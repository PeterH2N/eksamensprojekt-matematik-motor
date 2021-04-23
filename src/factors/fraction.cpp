#include "../expression.hpp"

Fraction::Fraction(std::vector<Token> tokens)
	: Factor(Factor::FactorType::Fraction)
{
	// find the divider
	long long operatorIndex = -1;
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].value == "(")
		{
			i = getParenthesisIndices(tokens, i).second;
		}
		else if (tokens[i].value == "/")
		{
			operatorIndex = i;
			break;
		}
	}

	if (tokens[operatorIndex - 1].value == ")")
		numerator = new Expression(getTokensFromIndices(tokens, std::pair<int,int>(1, operatorIndex - 2)));
	else
		numerator = new Expression(getTokensFromIndices(tokens, std::pair<int, int>(0, operatorIndex - 1)));

	if (tokens[operatorIndex + 1].value == "(")
		denominator = new Expression(getTokensFromIndices(tokens, std::pair<int, int>(operatorIndex + 2, tokens.size() - 2)));
	else
		denominator = new Expression(getTokensFromIndices(tokens, std::pair<int, int>(operatorIndex + 1, tokens.size() - 1)));

}

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

Factor::FactorType Fraction::getType()
{
	return type;
}

Factor* Fraction::multiply(Factor* s)
{
	return nullptr;
}

Factor* Fraction::divide(Factor* s)
{
	return nullptr;
}
