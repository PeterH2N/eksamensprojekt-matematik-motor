#include "../subexpression.hpp"
#include "../expression.hpp"

std::vector<Token> Fraction::getTokens()
{
	std::vector<Token> returnTokens;

	returnTokens.push_back(Token(Token::TokenType::Operator, "("));
	returnTokens.push_back(Token(Token::TokenType::Operator, "("));

	auto tempTokens = numerator->getTokens();

	returnTokens.insert(returnTokens.end(), tempTokens.begin(), tempTokens.end());

	returnTokens.push_back(Token(Token::TokenType::Operator, ")"));
	returnTokens.push_back(Token(Token::TokenType::Operator, "/"));
	returnTokens.push_back(Token(Token::TokenType::Operator, "("));

	tempTokens = denominator->getTokens();

	returnTokens.insert(returnTokens.end(), tempTokens.begin(), tempTokens.end());

	returnTokens.push_back(Token(Token::TokenType::Operator, ")"));
	returnTokens.push_back(Token(Token::TokenType::Operator, ")"));


	return returnTokens;

}

SubExpression::SubExpressionType Fraction::getType()
{
	return type;
}
