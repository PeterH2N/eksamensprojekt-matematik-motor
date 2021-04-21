#pragma once
#include "term.hpp"

class Expression
{
public:
	Expression(std::vector<Token> _tokens);
	~Expression();

	std::vector<Term*> terms;

	std::vector<Token> getTokens();

private:
	void organize(std::vector<Token> tokens);
};