#ifndef TOKEN_H
#define TOKEN_H

#include <algorithm>
#include <string>
#include <functional>
#include "helpfunctions.hpp"



class Token
{
public:
	enum class TokenType : int
	{
		Invalid,
		Identifier,
		Literal,
		Operator,
		Seperator,
		Function,
	};

	Token() {}
	Token(TokenType _type, std::string _value);

	TokenType type = TokenType::Invalid;
	std::string value;

	std::string TokenTypeString() const;

	std::string printString() const;


	friend std::ostream& operator<<(std::ostream& os, const Token& t);

	friend bool operator==(const Token& t1, const Token& t2);
};

Token::TokenType getTypeFromChar(char c);

#endif TOKEN_H