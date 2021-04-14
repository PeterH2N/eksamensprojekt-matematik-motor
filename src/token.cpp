#include "token.hpp"
#include <iostream>

Token::Token(TokenType _type, std::string _value)
	: type(_type), value(_value)
{
}

std::string Token::TokenTypeString() const
{
	switch ((int)this->type)
	{
	case (int)Token::TokenType::Identifier:
		return "identifier";
	case (int)Token::TokenType::Literal:
		return "literal";
	case (int)Token::TokenType::Operator:
		return "operator";
	case (int)Token::TokenType::Seperator:
		return "seperator";
	case (int)Token::TokenType::Function:
		return "function";
	default:
		return "invalid";
	}
}

std::string Token::printString() const
{
	return "(" + this->TokenTypeString() + ", " + this->value + ")";
}

std::vector<Token> lexify(std::string input)
{
	std::vector<Token> tokens;
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
			/*if (mapContainsKey(storedFunctions, buffer))
			{
				prevType = Token::TokenType::Function;
			}*/
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
			return std::vector<Token>();
		}

	}
	currentToken.type = currentType;
	currentToken.value = buffer;
	tokens.push_back(currentToken);

	return tokens;
}

std::ostream& operator<<(std::ostream& os, const Token& t)
{
	os << t.printString();
	return os;
}

bool operator==(const Token& t1, const Token& t2)
{
	return (t1.type == t2.type && t1.value == t2.value);
}

Token::TokenType getTypeFromChar(char c)
{
	if (arrayContains(Global::operators, c))
		return Token::TokenType::Operator;
	else if ((c >= 48 && c <= 57) || c == '.')
		return Token::TokenType::Literal;
	else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95)
		return Token::TokenType::Identifier;
	else if (arrayContains(Global::seperators, c))
		return Token::TokenType::Seperator;
	else
		return Token::TokenType::Invalid;
}