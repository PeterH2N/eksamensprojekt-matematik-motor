#include "token.h"
#include <iostream>

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

std::ostream& operator<<(std::ostream& os, const Token& t)
{
	os << t.printString();
	return os;
}

Token::TokenType getTypeFromChar(char c)
{
	if (arrayContains(operators, c))
		return Token::TokenType::Operator;
	else if ((c >= 48 && c <= 57) || c == '.')
		return Token::TokenType::Literal;
	else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95)
		return Token::TokenType::Identifier;
	else if (arrayContains(seperators, c))
		return Token::TokenType::Seperator;
	else
		return Token::TokenType::Invalid;
}