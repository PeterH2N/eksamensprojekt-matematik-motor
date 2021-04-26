#pragma once

#include "factor.hpp"

class Term
{
public:
	Term(const std::vector<Token>& _tokens);
	Term(const Term& t);
	~Term();

	std::vector<Factor*> factors;

	bool sign = true;

	std::vector<Token> getTokens();

	bool operator==(const Term& t2);

	bool operator!=(const Term& t2);

	void combineFactors();

	void multiply(const Term& t);

	void multiply(Factor* f);

};