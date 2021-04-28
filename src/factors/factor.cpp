#include "../factor.hpp"

Factor* Factor::Create(const std::vector<Token> tokens, const FactorType& type)
{
	switch (type)
	{
    case Factor::FactorType::Literal:
		return new Literal(tokens);
		break;
    case Factor::FactorType::Exponential:
		return new Exponential(tokens);
		break;
    case Factor::FactorType::Fraction:
		return new Fraction(tokens);
		break;
    case Factor::FactorType::Parenthesis:
		return new Parenthesis(tokens);
		break;
    case Factor::FactorType::Invalid:
		return nullptr;
		break;
	default:
		break;
	}
}

Factor::~Factor() {}

