#include "expression.h"
#include <iostream>


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



		if ((currentType == Token::TokenType::Literal && prevType == Token::TokenType::Literal) || (prevType == Token::TokenType::Literal && currentChar == '.' && !hasADecimal))
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
