#include "../expression.hpp"

Parenthesis::Parenthesis(const std::vector<Token>& tokens)
	: Factor(Factor::FactorType::Parenthesis)
{
	expression = new Expression(tokens);
}

Parenthesis::Parenthesis(const Parenthesis& p)
	: Factor(Factor::FactorType::Parenthesis)
{
	expression = new Expression(*p.expression);
}

Parenthesis::~Parenthesis()
{
	delete expression;
}

Factor* Parenthesis::Clone()
{
	return new Parenthesis(*this);
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

bool Parenthesis::operator==(Factor* f2)
{
	return false;
}

bool Parenthesis::operator!=(Factor* f2)
{
	return false;
}

