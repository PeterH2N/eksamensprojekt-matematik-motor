#pragma once
#include "term.hpp"

class Expression
{
public:
	Expression(std::vector<Token> _tokens);
	Expression(const Expression& e);
	~Expression();

	std::vector<Term*> terms;

	std::vector<Token> getTokens();

	bool operator==(const Expression& e2);
	bool operator!=(const Expression& e2);

	void multiply(Literal* l);

private:
	void organize(std::vector<Token> tokens);
};