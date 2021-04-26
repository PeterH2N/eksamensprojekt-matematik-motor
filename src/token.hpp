#pragma once
#include <string>
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

    friend std::vector<Token> lexify(std::string input);

	friend std::ostream& operator<<(std::ostream& os, const Token& t);

	friend bool operator==(const Token& t1, const Token& t2);

	friend Token::TokenType getTypeFromChar(char c);

    friend std::pair<int, int> getParenthesisIndices(std::vector<Token> tokens, int offset);

    friend std::vector<Token> getTokensFromIndices(const std::vector<Token>& tokens, std::pair<int, int> indices);

    friend std::string getStringFromTokens(const std::vector<Token>& tokens);
};

std::vector<Token> lexify(std::string input);

std::ostream& operator<<(std::ostream& os, const Token& t);

bool operator==(const Token& t1, const Token& t2);

Token::TokenType getTypeFromChar(char c);

std::pair<int, int> getParenthesisIndices(std::vector<Token> tokens, int offset = 0);

std::vector<Token> getTokensFromIndices(const std::vector<Token>& tokens, std::pair<int, int> indices);

std::string getStringFromTokens(const std::vector<Token>& tokens);

