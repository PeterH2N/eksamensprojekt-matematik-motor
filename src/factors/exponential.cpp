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

Factor* Exponential::divide(Factor* s)
{
	switch (s->type)
	{
	case FactorType::Literal:
	{
		Literal* l = dynamic_cast<Literal*>(s);
		return divide(l);
	}
	case FactorType::Fraction:
	{
		Fraction* l = dynamic_cast<Fraction*>(s);
		return divide(l);
	}
	case FactorType::Parenthesis:
	{
		Parenthesis* l = dynamic_cast<Parenthesis*>(s);
		return divide(l);
	}
	case FactorType::Exponential:
	{
		Exponential* l = dynamic_cast<Exponential*>(s);
		return divide(l);
	}
	default:
		break;
	}
	return nullptr;
}

bool Exponential::operator==(Factor* f2)
{
	if (type != f2->type)
		return false;
	auto f = dynamic_cast<Exponential*>(f2);

	return (*base == *f->base && *exponent == *f->exponent);


}

bool Exponential::operator!=(Factor* f2)
{
	return !(*this == f2);
}

Factor* Exponential::multiply(Literal* l)
{
	return nullptr;
}

Factor* Exponential::multiply(Fraction* f)
{
	auto returnFraction = new Fraction(*f);

	returnFraction->numerator->multiply(this);

	return returnFraction;
}

Factor* Exponential::multiply(Parenthesis* f)
{
	auto returnFactor = new Parenthesis(*f);

	returnFactor->expression->multiply(this);

	return returnFactor;
}

Factor* Exponential::multiply(Exponential* f)
{
	auto returnFactor = new Exponential(*f);

	if (*returnFactor->base == *base)
	{
		returnFactor->exponent->add(*exponent);
		return returnFactor;
	}

	return nullptr;
}

Factor* Exponential::divide(Literal* l)
{
	auto returnFactor = new Fraction();

	returnFactor->numerator = new Expression(this);
	returnFactor->denominator = new Expression(l);

	return returnFactor;
}

Factor* Exponential::divide(Fraction* f)
{
	auto returnFraction = new Fraction(*f);

	auto temp = returnFraction->numerator;
	returnFraction->numerator = returnFraction->denominator;
	returnFraction->denominator = temp;

	returnFraction->numerator->multiply(this);

	return returnFraction;
}

Factor* Exponential::divide(Parenthesis* f)
{
	auto returnFactor = new Fraction();

	returnFactor->numerator = new Expression(this);
	returnFactor->denominator = new Expression(*f->expression);

	return returnFactor;
}

Factor* Exponential::divide(Exponential* f)
{

	if (*base == *f->base)
	{
		auto returnFactor = new Exponential(*this);
		returnFactor->exponent->subtract(*f->exponent);
		return returnFactor;
	}
	auto returnFactor = new Fraction();

	returnFactor->numerator = new Expression(this);
	returnFactor->denominator = new Expression(f);

	return returnFactor;
}
