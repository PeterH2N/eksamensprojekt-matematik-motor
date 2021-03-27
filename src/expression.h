#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "token.h"

class Expression
{
public:
	Expression();
	Expression(std::string);
	Expression(std::vector<Token>);

	std::vector<Token> tokens;

	void lexify(std::string);

	Expression calculated();

	std::string printString() const;

	friend std::ostream& operator<<(std::ostream& os, const Expression& t);
};

#endif EXPRESSION_H