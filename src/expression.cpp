#include "expression.hpp"

Expression::Expression(std::vector<Token> _tokens)
{
	organize(_tokens);
}

std::vector<Token> Expression::getTokens()
{
	std::vector<Token> returnVector;

	for (auto subExpr : subExprs)
	{
		auto tempTokens = subExpr->getTokens();
		returnVector.insert(returnVector.end(), tempTokens.begin(), tempTokens.end());
	}
	return returnVector;
}

void Expression::organize(std::vector<Token> tokens)
{
}
