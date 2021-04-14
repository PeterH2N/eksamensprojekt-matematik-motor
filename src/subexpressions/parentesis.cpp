#include "../subexpression.hpp"
#include "../expression.hpp"

std::vector<Token> Parenthesis::getTokens()
{
	std::vector<Token> returnTokens;

	auto tempTokens = scalar->getTokens();

	returnTokens.insert(returnTokens.end(), tempTokens.begin(), tempTokens.end());

	returnTokens.push_back(Token(Token::TokenType::Operator, "*"));
		
	returnTokens.push_back(Token(Token::TokenType::Operator, "("));
	
	tempTokens = expression->getTokens();

	returnTokens.insert(returnTokens.end(), tempTokens.begin(), tempTokens.end());

	returnTokens.push_back(Token(Token::TokenType::Operator, ")"));

	return returnTokens;
}

SubExpression::SubExpressionType Parenthesis::getType()
{
	return type;
}