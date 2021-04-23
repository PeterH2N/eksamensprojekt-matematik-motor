#include "../factor.hpp"
#include <cmath>

Literal::Literal(std::vector<Token> tokens)
	: Factor(FactorType::Literal)
{
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].type == Token::TokenType::Literal)
		{
				if (i < tokens.size() - 1 && tokens[i + 1].value == "^")
				{
					value *= std::pow(std::stod(tokens[i].value), std::stod(tokens[i + 2].value));
					i += 2;
				}
				else
					value *= std::stod(tokens[i].value);
		}
		else if (tokens[i].type == Token::TokenType::Identifier)
		{
			// get exponent, if any
			bool isExponent = false;
			double exponent = 1;
			if (i < tokens.size() - 1)
			{
				// if the next token is a ^ we give it the literal next to it. Else, the exponent is just 1
				if (tokens[i + 1].value == "^")
				{
					exponent = std::stod(tokens[i + 2].value);
					isExponent = true;
				}
			}


			// check if identifier already exists
			bool exists = false;
			for (auto& identifier : identifiers)
			{
				if (identifier.first == tokens[i].value)
				{
					identifier.second += exponent;
					exists = true;
					break;
				}
			}
			if (!exists)
				identifiers.push_back(std::pair<std::string, double>(tokens[i].value, exponent));
			if (isExponent)
				i += 2;
		}
	}
}

std::vector<Token> Literal::getTokens()
{
	std::vector<Token> returnTokens;

	if (value != 1 || identifiers.size() == 0)
		returnTokens.push_back(Token(Token::TokenType::Literal, std::to_string(value)));


	for (auto identifier : identifiers)
	{
		if (value != 1)
			returnTokens.push_back(Token(Token::TokenType::Operator, "*"));

		if (identifier.second == 1)
		{
			returnTokens.push_back(Token(Token::TokenType::Identifier, identifier.first));
		}
		else
		{
			auto tempTokens = std::vector<Token>({ Token(Token::TokenType::Identifier, identifier.first), Token(Token::TokenType::Operator, "^"), Token(Token::TokenType::Literal, std::to_string(identifier.second)) });
			returnTokens.insert(returnTokens.end(), tempTokens.begin(), tempTokens.end());
		}

	}
	return returnTokens;
}

Factor::FactorType Literal::getType()
{
	return type;
}

Factor* Literal::multiply(Factor* s)
{
	return nullptr;
}

Factor* Literal::divide(Factor* s)
{
	return nullptr;
}
