#ifndef TOKEN_H
#define TOKEN_H

#include <algorithm>
#include <string>
#include <functional>
#include "helpfunctions.h"

static char operators[] = { '+', '-', '*', '/', '^', '=', '(', ')', ':' };
static char seperators[] = { ';' };
static std::map<std::string, double> identifiers;

class Token
{
public:
	enum class TokenType : int
	{
		Identifier,
		Literal,
		Operator,
		Seperator,
		Function,
		Invalid
	};

	TokenType type;
	std::string value;

	std::string TokenTypeString() const;

	std::string printString() const;


	friend std::ostream& operator<<(std::ostream& os, const Token& t);
};

Token::TokenType getTypeFromChar(char c);


static std::map< std::string, std::function<Token(std::vector<Token>)>> storedFunctions;

#endif TOKEN_H