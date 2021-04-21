#include "../expression.hpp"

Parenthesis::Parenthesis(std::vector<Token> tokens)
	: Factor(Factor::FactorType::Parenthesis)
{
	expression = new Expression(tokens);
}

std::vector<Token> Parenthesis::getTokens()
{
	std::vector<Token> returnTokens;

	std::vector<Token> tempTokens;
		
	returnTokens.push_back(Token(Token::TokenType::Operator, "("));
	
	tempTokens = expression->getTokens();

	returnTokens.insert(returnTokens.end(), tempTokens.begin(), tempTokens.end());

	returnTokens.push_back(Token(Token::TokenType::Operator, ")"));

	return returnTokens;
}

Factor::FactorType Parenthesis::getType()
{
	return type;
}

Factor* Parenthesis::multiply(Factor* s)
{
	return nullptr;
}

Factor* Parenthesis::divide(Factor* s)
{
	return nullptr;
}

