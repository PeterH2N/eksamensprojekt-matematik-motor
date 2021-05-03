#include "../expression.hpp"

Parenthesis::Parenthesis()
	: Factor(Factor::FactorType::Parenthesis) {}

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

Factor* Parenthesis::divide(Factor* s)
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

bool Parenthesis::operator==(Factor* f2)
{
	if (type == f2->type)
		return false;
	auto f = dynamic_cast<Parenthesis*>(f2);
	return *expression == *f->expression;
}

bool Parenthesis::operator!=(Factor* f2)
{
	return !(*this == f2);
}

Factor* Parenthesis::multiply(Literal* l)
{
	auto returnFactor = new Parenthesis(*this);

	returnFactor->multiply(l);

	return returnFactor;
}

Factor* Parenthesis::multiply(Fraction* f)
{
	auto returnFactor = new Fraction(*f);

	returnFactor->numerator->multiply(this);

	return returnFactor;
}

Factor* Parenthesis::multiply(Parenthesis* f)
{
	auto returnFactor = new Parenthesis(*this);

	returnFactor->expression->multiply(*f->expression);

	return returnFactor;
}

Factor* Parenthesis::multiply(Exponential* f)
{
	auto returnFactor = new Parenthesis(*this);

	returnFactor->expression->multiply(f);

	return returnFactor;
}

Factor* Parenthesis::divide(Literal* l)
{
	auto returnFactor = new Fraction();

	returnFactor->numerator = new Expression(*expression);
	returnFactor->denominator = new Expression(l);

	return returnFactor;
}

Factor* Parenthesis::divide(Fraction* f)
{
	auto returnFraction = new Fraction(*f);

	auto temp = returnFraction->numerator;
	returnFraction->numerator = returnFraction->denominator;
	returnFraction->denominator = temp;

	returnFraction->numerator->multiply(*expression);

	return returnFraction;
}

Factor* Parenthesis::divide(Parenthesis* f)
{
	auto returnFactor = new Fraction();

	returnFactor->numerator = new Expression(*expression);
	returnFactor->denominator = new Expression(*f->expression);

	return returnFactor;
}

Factor* Parenthesis::divide(Exponential* f)
{
	auto returnFactor = new Fraction();

	returnFactor->numerator = new Expression(*expression);
	returnFactor->denominator = new Expression(f);

	return returnFactor;
}

