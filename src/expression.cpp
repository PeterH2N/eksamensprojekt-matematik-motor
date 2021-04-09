#include "expression.h"
#include <iostream>
#include <cmath>


Expression::Expression()
{
}

Expression::Expression(std::string input)
{
	lexify(input);
	identify();
}

Expression::Expression(std::vector<Token> input)
{
	tokens = input;
	identify();
}

Expression::Expression(const Expression& c)
{
	tokens = c.tokens;
	identifiers = c.identifiers;
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
            tokens.clear();
			return;
		}

	}
	currentToken.type = currentType;
	currentToken.value = buffer;
	tokens.push_back(currentToken);
}

std::pair<int, int> Expression::getParenthesesIndices(int offset)
{
	size_t numLeftParentheses = 0, numRightParentheses = 0;
	size_t leftParenthesisIndex, rightParenthesisIndex;

	// looping though the tokens
	for (size_t i = offset; i < tokens.size(); i++)
	{
		// if we encounter a left parenthesis
		if (tokens[i].type == Token::TokenType::Operator && tokens[i].value == "(")
		{
			// update index and number of opening parentheses
			leftParenthesisIndex = i;
			numLeftParentheses++;
			for (size_t j = i + 1; j < tokens.size(); j++)
			{
				// if we find more left parentheses, add to the count, and the same with right ones
				if (tokens[j].type == Token::TokenType::Operator && tokens[j].value == "(")
					numLeftParentheses++;
				else if (tokens[j].type == Token::TokenType::Operator && tokens[j].value == ")")
					numRightParentheses++;

				// once there is the same amount of each, the first we found must have been closed.
				if (numLeftParentheses == numRightParentheses)
				{
					rightParenthesisIndex = j;
					return std::pair<int, int>(leftParenthesisIndex, rightParenthesisIndex);
				}
			}
		}
	}
	return std::pair<int, int>(0, 0);
}


void Expression::identify()
{
	identifiers.clear();
	int lastTermIndex = 0;
	for (size_t i = 1; i < tokens.size(); i++)
	{
		// parentheses are found and the contents excluded from th search. They are meant to be "lifted" later.
		if (tokens[i].value == "(")
		{
			auto indices = getParenthesesIndices(i);
			identifiers.push_back(SubExprIdentifier(indices, SubExprIdentifier::SubExprType::Parenthesis));
			i = indices.second + size_t(1);
		}

		// finding terms - encounter a plus / minus since last plus / minus
		else if (tokens[i].value == "+" || tokens[i].value == "-")
		{
			identifiers.push_back(SubExprIdentifier(std::pair<int, int>( lastTermIndex == 0 ? 0 : lastTermIndex - 1, i - 1), SubExprIdentifier::SubExprType::Term));
			lastTermIndex = i + 1;
		}
		else if (i >= tokens.size() - 1)
		{
			identifiers.push_back(SubExprIdentifier(std::pair<int, int>( lastTermIndex == 0 ? 0 : lastTermIndex - 1, i), SubExprIdentifier::SubExprType::Term));
		}
			
	}

}

Expression Expression::subExprFromIndices(std::pair<int,int> indices) const
{
	return Expression(std::vector<Token>(&tokens[indices.first], &tokens[indices.second] + 1));
}

Expression Expression::replaceByIndices(Expression replacement, std::pair<int, int> indices) const
{
	Expression returnExpr(tokens);
	// remove parenthesis from expression
	returnExpr.tokens.erase(returnExpr.tokens.begin() + indices.first, returnExpr.tokens.begin() + indices.second + 1);
	// insert the evaluated expression instead
	returnExpr.tokens.insert(returnExpr.tokens.begin() + indices.first, replacement.tokens.begin(), replacement.tokens.end());

	return returnExpr;
}

Expression Expression::calculated() const
{
	// using PEMDAS, we calculate the result (only works with literals)
	Expression returnExpr(tokens);
	// parentheses
	{
		int offset = 0;
		for (std::pair<int, int> indices = returnExpr.getParenthesesIndices(); indices != std::pair<int, int>(0, 0); indices = returnExpr.getParenthesesIndices(offset))
		{
            Expression subExpr = returnExpr.subExprFromIndices(std::pair<int,int> (indices.first + 1,indices.second - 1));
			subExpr = subExpr.calculated();
			// remove parenthesis from expression
			returnExpr = returnExpr.replaceByIndices(subExpr, indices);
			offset += subExpr.tokens.size() - 1;
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

Expression Expression::solveLinearEquation()
{
	int equalsIndex = -1;
	std::string identifier;
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].type == Token::TokenType::Identifier)
			identifier = tokens[i].value;
		if (tokens[i].value == "=")
		{
			equalsIndex = i;
			break;
		}
	}
	// return invalid if there is no equals sign.
	if (equalsIndex == -1)
		return Expression({ Token(Token::TokenType::Invalid, "")});

	Expression leftSide(subExprFromIndices({ 0, equalsIndex - 1 }));
	Expression rightSide(subExprFromIndices({ equalsIndex + 1, tokens.size() - 1 }));

	// count together all the literals on each side

	// leftSide
	double leftSideLiterals = 0;
	for (size_t i = 0; i < leftSide.identifiers.size(); i++)
	{
		if (leftSide.identifiers[i].type == SubExprIdentifier::SubExprType::Term)
		{
			bool termIsLiteral = true;
			for (size_t j = leftSide.identifiers[i].indices.first; j <= leftSide.identifiers[i].indices.second; j++)
				if (!(leftSide.tokens[j].type == Token::TokenType::Literal || leftSide.tokens[j].type == Token::TokenType::Operator))
				{
					termIsLiteral = false;
					break;
				}

			if (termIsLiteral)
			{
				Expression subExpr = leftSide.subExprFromIndices(leftSide.identifiers[i].indices);
				if (subExpr.tokens[0].value == "-")
					subExpr.tokens.insert(subExpr.tokens.begin(), Token(Token::TokenType::Literal, "0"));
				else if (subExpr.tokens[0].value == "+")
					subExpr.tokens.erase(subExpr.tokens.begin());
				subExpr = subExpr.calculated();
				leftSideLiterals += std::stod(subExpr.tokens[0].value);
				// removing the term from expression, as it has now been counted.
				leftSide = leftSide.replaceByIndices(Expression(), leftSide.identifiers[i].indices);
				leftSide.identify();
				i--;
			}
		}
	}
	

	// rightSide - same code as above
	double rightSideLiterals = 0;
	for (size_t i = 0; i < rightSide.identifiers.size(); i++)
	{
		if (rightSide.identifiers[i].type == SubExprIdentifier::SubExprType::Term)
		{
			bool termIsLiteral = true;
			for (size_t j = rightSide.identifiers[i].indices.first; j <= rightSide.identifiers[i].indices.second; j++)
				if (!(rightSide.tokens[j].type == Token::TokenType::Literal || rightSide.tokens[j].type == Token::TokenType::Operator))
					termIsLiteral = false;

			if (termIsLiteral)
			{
				Expression subExpr = rightSide.subExprFromIndices(rightSide.identifiers[i].indices);
				if (subExpr.tokens[0].value == "-")
					subExpr.tokens.insert(subExpr.tokens.begin(), Token(Token::TokenType::Literal, "0"));
				else if (subExpr.tokens[0].value == "+")
					subExpr.tokens.erase(subExpr.tokens.begin());
				subExpr = subExpr.calculated();
				rightSideLiterals += std::stod(subExpr.tokens[0].value);
				// removing the term from expression, as it has now been counted.
				rightSide = rightSide.replaceByIndices(Expression(), rightSide.identifiers[i].indices);
				rightSide.identify();
				i--;
			}
		}
	}

	// subtracting the left side from the right, to remove any literals from left side.
	rightSideLiterals -= leftSideLiterals;
	leftSideLiterals = 0;

	// removing unneccesary signs
	// left side
	if (leftSide.tokens[0].value == "+")
		leftSide.tokens.erase(leftSide.tokens.begin());
	else if (leftSide.tokens[0].value == "-")
	{
		leftSide.tokens.erase(leftSide.tokens.begin());
		leftSide.tokens[0].value = std::to_string(-1 * std::stod(leftSide.tokens[0].value));
	}
	// right side
	if (rightSide.tokens[0].value == "+")
		rightSide.tokens.erase(rightSide.tokens.begin());
	else if (rightSide.tokens[0].value == "-")
	{
		rightSide.tokens.erase(rightSide.tokens.begin());
		rightSide.tokens[0].value = std::to_string(-1 * std::stod(rightSide.tokens[0].value));
	}


	leftSide.identify();
	rightSide.identify();


	// making sure all identifiers have a literal before them
	for (size_t i = 0; i < leftSide.identifiers.size(); i++)
	{
		Expression subExpr = leftSide.subExprFromIndices(leftSide.identifiers[i].indices);
		if (subExpr.tokens[0].type == Token::TokenType::Identifier)
		{
			subExpr.tokens.insert(subExpr.tokens.begin(), { Token(Token::TokenType::Literal, "1"), Token(Token::TokenType::Operator, "*") });
		}
	}
	for (size_t i = 0; i < rightSide.identifiers.size(); i++)
	{
		Expression subExpr = rightSide.subExprFromIndices(rightSide.identifiers[i].indices);
		if (subExpr.tokens[0].type == Token::TokenType::Identifier)
		{
			subExpr.tokens.insert(subExpr.tokens.begin(), { Token(Token::TokenType::Literal, "1"), Token(Token::TokenType::Operator, "*") });
		}
	}

	// counting up all the identifiers. same principle as above
	// all of the terms that are left should contain the same identifier.
	// left side
	double numLeftSideIdentifiers = 0, numRightSideIdentifiers = 0;
	for (size_t i = 0; i < leftSide.identifiers.size(); i++)
	{
		Expression subExpr = leftSide.subExprFromIndices(leftSide.identifiers[i].indices);

		// removing unnescessary signs.
		if (subExpr.tokens[0].value == "+")
			subExpr.tokens.erase(subExpr.tokens.begin());
		else if (subExpr.tokens[0].value == "-")
		{
			subExpr.tokens.erase(subExpr.tokens.begin());
			subExpr.tokens[0].value = std::to_string(-1 * std::stod(subExpr.tokens[0].value));
		}
		
		for (size_t j = 0; j < subExpr.tokens.size(); j++)
		{
			if (subExpr.tokens[j].type == Token::TokenType::Identifier)
			{
				Expression scalar = subExpr.subExprFromIndices(std::pair<int,int>(0, j - 2));
				scalar = scalar.calculated();
				numLeftSideIdentifiers += std::stod(scalar.tokens[0].value);
			}
		}
	}
	// right side
	for (size_t i = 0; i < rightSide.identifiers.size(); i++)
	{
		Expression subExpr = rightSide.subExprFromIndices(rightSide.identifiers[i].indices);

		// removing unnescessary signs.
		if (subExpr.tokens[0].value == "+")
			subExpr.tokens.erase(subExpr.tokens.begin());
		else if (subExpr.tokens[0].value == "-")
		{
			subExpr.tokens.erase(subExpr.tokens.begin());
			subExpr.tokens[0].value = std::to_string(-1 * std::stod(subExpr.tokens[0].value));
		}

		for (size_t j = 0; j < subExpr.tokens.size(); j++)
		{
			if (subExpr.tokens[j].type == Token::TokenType::Identifier)
			{
				Expression scalar = subExpr.subExprFromIndices(std::pair<int, int>(0, j - 2));
				scalar = scalar.calculated();
				numRightSideIdentifiers += std::stod(scalar.tokens[0].value);
			}
		}
	}

	// isolating x, by moving them to the left side.
	numLeftSideIdentifiers -= numRightSideIdentifiers;
	numRightSideIdentifiers = 0;

	// now dividing by the scalar to get the result for 'x'
	double result = rightSideLiterals / numLeftSideIdentifiers;

	std::vector<Token> resultTokens = { Token(Token::TokenType::Identifier, identifier), Token(Token::TokenType::Operator, "="), Token(Token::TokenType::Literal, std::to_string(result)) };

	return Expression(resultTokens);
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

Expression::SubExprIdentifier::SubExprIdentifier(std::pair<int, int> _indices, SubExprType _type)
	: type(_type), indices(_indices)
{

}
