#pragma once
#include "subexpression.hpp"

class Expression
{
public:
	Expression(std::vector<Token> _tokens);
	~Expression()
	{
		for (auto subExpr : subExprs)
			delete subExpr;
	}
	std::vector<SubExpression*> subExprs;

	std::vector<Token> getTokens();

private:
	void organize(std::vector<Token> tokens);
};