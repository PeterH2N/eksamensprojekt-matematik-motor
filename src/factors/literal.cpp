#include "expression.hpp"
#include <cmath>

Literal::Literal(const Literal& l)
	: Factor(FactorType::Literal)
{
	value = l.value;
	identifiers = l.identifiers;
}

Literal::Literal(const std::vector<Token>& tokens)
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

Factor* Literal::Clone()
{
	return new Literal(*this);
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
	switch (s->type)
	{
	case FactorType::Literal:
	{
		Literal* l = dynamic_cast<Literal*>(s);
		return multiply(l);
	}
	case FactorType::Fraction:
	{
		Fraction* l = dynamic_cast<Fraction*>(s);
		return multiply(l);
	}
	case FactorType::Parenthesis:
	{
		Parenthesis* l = dynamic_cast<Parenthesis*>(s);
		return multiply(l);
	}
	case FactorType::Exponential:
	{
		Exponential* l = dynamic_cast<Exponential*>(s);
		return multiply(l);
	}
	default:
		break;
	}
	return nullptr;
}

Factor* Literal::divide(Factor* s)
{
	return nullptr;
}

bool Literal::operator==(Factor* f2)
{
	if (type != f2->type)
		return false;
	else
	{
		Literal* l2 = dynamic_cast<Literal*>(f2);
		return (identifiers == l2->identifiers && value == l2->value);
	}
}

bool Literal::operator!=(Factor* f2)
{
	return !(*this == f2);
}

Factor* Literal::multiply(Literal* l)
{
	Literal* returnFactor = new Literal(*this);
	returnFactor->value *= l->value;

	for (int i = 0; i < l->identifiers.size(); i++)
	{
		// if identifier is already in our vector
		int identIndex = -1;
		for (int j = 0; j < returnFactor->identifiers.size(); j++)
		{
			if (l->identifiers[i].first == returnFactor->identifiers[j].first)
			{
				identIndex = j;
				break;
			}
		}

		if (identIndex != -1)
		{
			returnFactor->identifiers[identIndex].second += l->identifiers[i].second;
		}
		else
		{
			returnFactor->identifiers.push_back(l->identifiers[i]);
		}
	}
	return returnFactor;
}

Factor* Literal::multiply(Fraction* f)
{
	auto returnFraction = new Fraction(*f);

	returnFraction->numerator->multiply(this);
	return returnFraction;
}

Factor* Literal::multiply(Parenthesis* p)
{
	auto returnFraction = new Parenthesis(*p);

	returnFraction->expression->multiply(this);
	return returnFraction;
}

Factor* Literal::multiply(Exponential* p)
{
	return nullptr;
}

Factor* Literal::divide(Literal* l)
{
	return nullptr;
}
