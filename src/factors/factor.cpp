#include "../factor.hpp"

Factor* Factor::Create(const std::vector<Token> tokens, const FactorType& type)
{
	switch (type)
	{
    case (int)Factor::FactorType::Literal:
		return new Literal(tokens);
		break;
    case (int)Factor::FactorType::Exponential:
		return new Exponential(tokens);
		break;
    case (int)Factor::FactorType::Fraction:
		return new Fraction(tokens);
		break;
    case (int)Factor::FactorType::Parenthesis:
		return new Parenthesis(tokens);
		break;
    case (int)Factor::FactorType::Invalid:
		return nullptr;
		break;
	default:
		break;
	}
}

Factor::~Factor() {}

