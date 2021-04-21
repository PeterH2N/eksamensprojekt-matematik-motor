#pragma once

#include "factor.hpp"

class Term
{
public:
	Term(std::vector<Token> _tokens);
	~Term();

	std::vector<Factor*> factors;

	bool sign = true;

	std::vector<Token> getTokens();
};