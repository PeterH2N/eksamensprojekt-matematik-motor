#include "../expression.hpp"

Exponential::Exponential()
	: Factor(Factor::FactorType::Exponential) {}

Exponential::Exponential(const std::vector<Token>& tokens)
	: Factor(Factor::FactorType::Exponential)
{
	// find the exponent operator
	int operatorIndex = -1;
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].value == "(")
		{
			i = getParenthesisIndices(tokens, i).second;
		}
		if (tokens[i].value == "^")
		{
			operatorIndex = i;
			break;
		}
	}

	if (tokens[operatorIndex - 1].value == ")")
		base = new Expression(getTokensFromIndices(tokens, std::pair<int, int>(1, operatorIndex - 2)));
	else
		base = new Expression(getTokensFromIndices(tokens, std::pair<int, int>(0, operatorIndex - 1)));

	if (tokens[operatorIndex + 1].value == "(")
		exponent = new Expression(getTokensFromIndices(tokens, std::pair<int, int>(operatorIndex + 2, tokens.size() - 2)));
	else
		exponent = new Expression(getTokensFromIndices(tokens, std::pair<int, int>(operatorIndex + 1, tokens.size() - 1)));
	
}

Exponential::Exponential(const Exponential& e)
	: Factor(Factor::FactorType::Exponential)
{
	base = new Expression(*e.base);
	exponent = new Expression(*e.exponent);
}

Exponential::~Exponential()
{
	delete base;
	delete exponent;
}

Factor* Exponential::Clone()
{
	return new Exponential(*this);
}

std::vector<Token> Exponential::getTokens()
{
	std::vector<Token> returnVector;

	auto tempTokens = base->getTokens();

	if (base->terms.size() > 1)
		returnVector.push_back(Token(Token::TokenType::Operator, "("));
	returnVector.insert(returnVector.end(), tempTokens.begin(), tempTokens.end());
	if (base->terms.size() > 1)
		returnVector.push_back(Token(Token::TokenType::Operator, ")"));

	returnVector.push_back(Token(Token::TokenType::Operator, "^"));

	tempTokens = exponent->getTokens();

	if (exponent->terms.size() > 1)
		returnVector.push_back(Token(Token::TokenType::Operator, "("));
	returnVector.insert(returnVector.end(), tempTokens.begin(), tempTokens.end());
	if (exponent->terms.size() > 1)
		returnVector.push_back(Token(Token::TokenType::Operator, ")"));

	return returnVector;
}

Factor::FactorType Exponential::getType()
{
	return type;
}

Factor* Exponential::multiply(Factor* s)
{
	return nullptr;
}

Factor* Exponential::divide(Factor* s)
{
	return nullptr;
}

bool Exponential::operator==(Factor* f2)
{
	return false;
}

bool Exponential::operator!=(Factor* f2)
{
	return false;
}
