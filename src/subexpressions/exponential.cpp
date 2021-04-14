#include "../subexpression.hpp"
#include "../expression.hpp"

std::vector<Token> Exponential::getTokens()
{
	std::vector<Token> returnVector;

	auto tempTokens = base->getTokens();

	returnVector.insert(returnVector.end(), tempTokens.begin(), tempTokens.end());

	returnVector.push_back(Token(Token::TokenType::Operator, "^"));

	tempTokens = exponent->getTokens();

	returnVector.insert(returnVector.end(), tempTokens.begin(), tempTokens.end());

	return std::vector<Token>();
}

SubExpression::SubExpressionType Exponential::getType()
{
	return type;
}