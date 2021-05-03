#pragma once
#include "term.hpp"

class Expression
{
public:
	Expression(std::vector<Token> _tokens);
	Expression(const Term& t);
	Expression(Factor* f);
	Expression(const Expression& e);
	~Expression();

	std::vector<Term*> terms;

	std::vector<Token> getTokens();

	bool operator==(const Expression& e2);
	bool operator!=(const Expression& e2);

	void multiply(Factor* f);

	void multiply(const Expression& e);
	void divide(const Expression& e);

	void add(const Expression& e);
	void subtract(const Expression& e);

private:
	void organize(std::vector<Token> tokens);
};