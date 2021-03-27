#include "expression.h"
#include <iostream>
#include <cmath>


Expression::Expression()
{
}

Expression::Expression(std::string input)
{
	this->lexify(input);
}

Expression::Expression(std::vector<Token> input)
{
	this->tokens = input;
}

void Expression::lexify(std::string input)
{
	input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
	tokens.clear();
	Token currentToken;
	char currentChar;
	Token::TokenType currentType = Token::TokenType::Invalid, prevType;
	std::string buffer;
	bool hasADecimal = false;

	currentChar = input[0];
	prevType = getTypeFromChar(currentChar);

	buffer = currentChar;

	for (size_t i = 1; i < input.size(); i++)
	{
		currentChar = input[i];
		currentType = getTypeFromChar(currentChar);


		if (prevType == Token::TokenType::Operator)
		{
			currentToken.type = prevType;
			currentToken.value = buffer;
			buffer = currentChar;
			prevType = currentType;
			tokens.push_back(currentToken);
		}
		else if ((currentType == Token::TokenType::Literal && prevType == Token::TokenType::Literal) || (prevType == Token::TokenType::Literal && currentChar == '.' && !hasADecimal))
		{
			if (currentChar == '.')
				hasADecimal = true;
			buffer += currentChar;
		}
		else if (prevType == Token::TokenType::Identifier && (currentType == Token::TokenType::Identifier || currentType == Token::TokenType::Literal))
		{
			buffer += currentChar;
		}
		else if (currentType != prevType)
		{
			if (mapContainsKey(storedFunctions, buffer))
			{
				prevType = Token::TokenType::Function;
			}
			hasADecimal = false;
			currentToken.type = prevType;
			currentToken.value = buffer;
			tokens.push_back(currentToken);
			buffer = currentChar;
			prevType = currentType;
		}
		else if (currentType == Token::TokenType::Invalid)
		{
			std::cout << "Invalid character in expression at character " + i + 1 << std::endl;
			tokens = {};
			return;
		}

	}
	currentToken.type = currentType;
	currentToken.value = buffer;
	tokens.push_back(currentToken);
}

Expression Expression::calculated()
{
	// using PEMDAS, we calculate the result (only works with literals)
	Expression returnExpr(tokens);
	// parentheses
	{
		size_t numLeftParentheses = 0, numRightParentheses = 0;
		size_t leftParenthesisIndex, rightParenthesisIndex;

		// looping though the tokens
		for (size_t i = 0; i < returnExpr.tokens.size(); i++)
		{
			// if we encounter a left parenthesis
			if (returnExpr.tokens[i].type == Token::TokenType::Operator && returnExpr.tokens[i].value == "(")
			{
				// update index and number of opening parentheses
				leftParenthesisIndex = i;
				numLeftParentheses++;
				for (size_t j = i + 1; j < returnExpr.tokens.size(); j++)
				{
					// if we find more left parentheses, add to the count, and the same with right ones
					if (returnExpr.tokens[j].type == Token::TokenType::Operator && returnExpr.tokens[j].value == "(")
						numLeftParentheses++;
					else if (returnExpr.tokens[j].type == Token::TokenType::Operator && returnExpr.tokens[j].value == ")")
						numRightParentheses++;
					
					// once there is the same amount of each, the first we found must have been closed.
					if (numLeftParentheses == numRightParentheses)
					{
						rightParenthesisIndex = j;
						// making a new expression containing the contents of the parentesis, and evaluating it (recursion)
						Expression subExpr(std::vector<Token>(&returnExpr.tokens[leftParenthesisIndex + size_t(1)], &returnExpr.tokens[rightParenthesisIndex]));
						subExpr = subExpr.calculated();
						// remove parenthesis from expression
						returnExpr.tokens.erase(returnExpr.tokens.begin() + leftParenthesisIndex, returnExpr.tokens.begin() + rightParenthesisIndex + 1);
						// insert the evaluated expression instead
						returnExpr.tokens.insert(returnExpr.tokens.begin() + leftParenthesisIndex, subExpr.tokens.begin(), subExpr.tokens.end());
						i += subExpr.tokens.size() - 1;
						numLeftParentheses = 0;
						numRightParentheses = 0;
						leftParenthesisIndex = 0;
						rightParenthesisIndex = 0;
						break;
					}
				}

			}
		}

	}

	// exponents
	{
		for (size_t i = 0; i < returnExpr.tokens.size(); i++)
		{
			// find the power operator
			if (returnExpr.tokens[i].type == Token::TokenType::Operator && returnExpr.tokens[i].value == "^")
			{
				// calculate result
				double base, exponent;
				base = std::stod(returnExpr.tokens[i - 1].value);
				exponent = std::stod(returnExpr.tokens[i + 1].value);
				double result = std::pow(base, exponent);
				Token resultToken(Token::TokenType::Literal, std::to_string(result));
				// remove from expression
				returnExpr.tokens.erase(returnExpr.tokens.begin() + (i - 1), returnExpr.tokens.begin() + (i + 2));
				// insert resulting literal
				returnExpr.tokens.insert(returnExpr.tokens.begin() + (i - 1), resultToken);
				i--;
			}
		}
	}

	// mulpiplikation and division
	{
		for (size_t i = 0; i < returnExpr.tokens.size(); i++)
		{
			// find the operator
			if (returnExpr.tokens[i].type == Token::TokenType::Operator && (returnExpr.tokens[i].value == "*" || returnExpr.tokens[i].value == "/"))
			{
				// calculate result
				double value1, value2;
				value1 = std::stod(returnExpr.tokens[i - 1].value);
				value2 = std::stod(returnExpr.tokens[i + 1].value);
				
				double result = 0;
				if (returnExpr.tokens[i].value == "*")
					result = value1 * value2;
				else
					result = value1 / value2;

				Token resultToken(Token::TokenType::Literal, std::to_string(result));
				// remove from expression
				returnExpr.tokens.erase(returnExpr.tokens.begin() + (i - 1), returnExpr.tokens.begin() + (i + 2));
				// insert resulting literal
				returnExpr.tokens.insert(returnExpr.tokens.begin() + (i - 1), resultToken);
				i--;
			}
		}
	}

	// addition and subtraction
	{
		for (size_t i = 0; i < returnExpr.tokens.size(); i++)
		{
			// find the operator
			if (returnExpr.tokens[i].type == Token::TokenType::Operator && (returnExpr.tokens[i].value == "+" || returnExpr.tokens[i].value == "-"))
			{
				// calculate result
				double value1, value2;
				value1 = std::stod(returnExpr.tokens[i - 1].value);
				value2 = std::stod(returnExpr.tokens[i + 1].value);

				double result = 0;
				if (returnExpr.tokens[i].value == "+")
					result = value1 + value2;
				else
					result = value1 - value2;

				Token resultToken(Token::TokenType::Literal, std::to_string(result));
				// remove from expression
				returnExpr.tokens.erase(returnExpr.tokens.begin() + (i - 1), returnExpr.tokens.begin() + (i + 2));
				// insert resulting literal
				returnExpr.tokens.insert(returnExpr.tokens.begin() + (i - 1), resultToken);
				i--;
			}
		}
	}

	return returnExpr;
}

std::string Expression::printString() const
{
	std::string returnString = "";
	for (int i = 0; i < tokens.size(); i++)
	{
		returnString += tokens[i].printString();
		if (i < tokens.size() - 1)
			returnString += ", ";
	}
	return returnString;
}

std::ostream& operator<<(std::ostream& os, const Expression& e)
{
	os << e.printString();
	return os;
}
