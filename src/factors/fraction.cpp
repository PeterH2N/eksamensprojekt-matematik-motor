#include "../expression.hpp"

Fraction::Fraction()
	: Factor(Factor::FactorType::Fraction) {}

Fraction::Fraction(const std::vector<Token>& tokens)
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

Fraction::Fraction(const Fraction& f)
	: Factor(Factor::FactorType::Fraction)
{
	numerator = new Expression(*f.numerator);
	denominator = new Expression(*f.denominator);
}

Fraction::~Fraction()
{
	delete numerator;
	delete denominator;
}

Factor* Fraction::Clone()
{
	return new Fraction(*this);
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

bool Fraction::operator==(Factor* f2)
{
	if (f2->type != type)
		return false;
	auto fr2 = dynamic_cast<Fraction*>(f2);
	return (*numerator == *fr2->numerator && *denominator == *fr2->denominator);
}

bool Fraction::operator!=(Factor* f2)
{
	return false;
}

Factor* Fraction::multiply(Literal* l)
{
	Fraction* returnFraction = new Fraction(*this);

	returnFraction->numerator->multiply(l);

	return returnFraction;
}

Factor* Fraction::multiply(Fraction* f)
{
	Fraction* returnFraction = new Fraction(*this);

	returnFraction->numerator->multiply(*f->numerator);
	returnFraction->denominator->multiply(*f->denominator);


	return returnFraction;
}

Factor* Fraction::multiply(Parenthesis* p)
{
	return nullptr;
}

Factor* Fraction::multiply(Exponential* p)
{
	return nullptr;
}

Factor* Fraction::divide(Literal* l)
{
    Fraction* returnFraction = new Fraction(*this);

    returnFraction->denominator->multiply(l);

    return returnFraction;

}

Factor* Fraction::divide(Fraction* f)
{
    Fraction* returnFraction = new Fraction(*this);

    returnFraction->numerator->multiply(*f->denominator);
    returnFraction->denominator->multiply(*f->numerator);

    return returnFraction;

}

Factor* Fraction::divide(Parenthesis* p)
{
    Fraction* returnFraction = new Fraction(*this);

    returnFraction->denominator->multiply(p);

    return returnFraction;

}

Factor* Fraction::divide(Exponential* p)
{
    Fraction* returnFraction = new Fraction(*this);

    returnFraction->denominator->multiply(p);

    return returnFraction;
}
