#include "term.hpp"
#include "expression.hpp"

Term::Term(const std::vector<Token>& _tokens)
{
	auto tokens = _tokens;
	if (tokens[0].value == "-")
	{
		sign = false;
		tokens.erase(tokens.begin());
	}
	else if (tokens[0].value == "+")
	{
		sign = true;
		tokens.erase(tokens.begin());
	}
	else sign = true;

	// check from left to right
	int lastCutOff = 0;
	Factor::FactorType currentType = Factor::FactorType::Literal;
	for (int i = 0; i < tokens.size(); i++)
	{

		// if we encounter a token that is part of literal
		if ((tokens[i].type == Token::TokenType::Identifier || tokens[i].type == Token::TokenType::Literal || tokens[i].value == "*") || (tokens[i].value == "^" && tokens[i + 1].type == Token::TokenType::Literal))
		{
			currentType = Factor::FactorType::Literal;
			// if this is the last token
			if (i == tokens.size() - 1)
			{
				auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff, i));
				factors.push_back(Factor::Create(factorTokens, currentType));
			}
		}
		else
		{
			if (i != 0 && currentType == Factor::FactorType::Literal && tokens[i].value != "^" && tokens[i].value != "/")
			{
				auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff, i - 1));
				factors.push_back(Factor::Create(factorTokens, currentType));
			}
			if (tokens[i].value == "^")
			{
				if (i > 1)
				{
					auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff, i - 2));
					factors.push_back(Factor::Create(factorTokens, currentType));
					lastCutOff = i - 1;
				}
				currentType = Factor::FactorType::Exponential;
				if (tokens[i + 1].value == "(")
				{
					i = getParenthesisIndices(tokens, i).second;
					auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff, i));
					factors.push_back(Factor::Create(factorTokens, currentType));
				}
				else
				{
					auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff, i + 1));
					factors.push_back(Factor::Create(factorTokens, currentType));
					i++;
				}


			}
			else if (tokens[i].value == "/")
			{
				if (i > 1)
				{
					auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff, i - 2));
					factors.push_back(Factor::Create(factorTokens, currentType));
					lastCutOff = i - 1;
				}
				lastCutOff = i - 1;
				currentType = Factor::FactorType::Fraction;
				if (tokens[i + 1].value == "(")
				{
					i = getParenthesisIndices(tokens, i).second;
					auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff, i));
					factors.push_back(Factor::Create(factorTokens, currentType));
				}
				else
				{
					i++;
					auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff, i));
					factors.push_back(Factor::Create(factorTokens, currentType));
					lastCutOff = i + 1;
				}
			}
			else if (tokens[i].value == "(")
			{
				lastCutOff = i;
				currentType = Factor::FactorType::Parenthesis;
				i = getParenthesisIndices(tokens, i).second + 1;
				if (i >= tokens.size() - 1)
				{
					// type is parenthesis
					auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff + 1, i - 2));
					factors.push_back(Factor::Create(factorTokens, currentType));
				}
				else if (tokens[i].value == "^")
				{
					currentType = Factor::FactorType::Exponential;
					if (tokens[i + 1].value == "(")
					{
						i = getParenthesisIndices(tokens, i).second;
						auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff, i));
						factors.push_back(Factor::Create(factorTokens, currentType));
					}
					else
					{
						i++;
						auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff, i));
						factors.push_back(Factor::Create(factorTokens, currentType));
					}

				}
				else if (tokens[i].value == "/")
				{
					currentType = Factor::FactorType::Fraction;
					if (tokens[i + 1].value == "(")
					{
						i = getParenthesisIndices(tokens, i).second;
						auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff, i));
						factors.push_back(Factor::Create(factorTokens, currentType));
					}
					else
					{
						i++;
						auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff, i));
						factors.push_back(Factor::Create(factorTokens, currentType));
					}
				}
				else
				{
					// type is parenthesis
					auto factorTokens = getTokensFromIndices(tokens, std::pair<int, int>(lastCutOff + 1, i - 1));
					factors.push_back(Factor::Create(factorTokens, currentType));
				}

			}
			lastCutOff = 1 + i;
		}
	}

}

Term::Term(Factor* f)
{
	factors.push_back(f);
}

Term::Term(std::vector<Factor*> _factors)
{
	for (auto factor : _factors)
	{
		factors.push_back(factor->Clone());
	}
}

Term::Term(const Term& t)
{
	sign = t.sign;
	for (auto factor : t.factors)
	{
		factors.push_back(factor->Clone());
	}
}

Term::~Term()
{
	for (auto factor : factors)
		delete factor;
}

std::vector<Token> Term::getTokens()
{
	std::vector<Token> returnTokens;

	if (sign)
		returnTokens.push_back(Token(Token::TokenType::Operator, "+"));
	else
		returnTokens.push_back(Token(Token::TokenType::Operator, "-"));
	
	for (int i = 0; i < factors.size(); i++)
	{
		std::vector<Token> tempTokens = factors[i]->getTokens();
		returnTokens.insert(returnTokens.end(), tempTokens.begin(), tempTokens.end());
		if (i != factors.size() - 1)
			returnTokens.push_back(Token(Token::TokenType::Operator, "*"));
	}
	return returnTokens;
}

bool Term::operator==(const Term& t2)
{
	if (factors.size() != t2.factors.size() || sign != t2.sign)
		return false;

	// even if the factors are out of order, they still evaluate to the same. Therefore we need to make sure that each factor in one term is also existant in the other.
	for (int i = 0; i < factors.size(); i++)
	{
		bool exists = false;
		for (int j = 0; j < factors.size(); j++)
		{
			if (*t2.factors[i] == factors[j])
				exists = true;
		}
		if (!exists)
			return false;
	}

	return true;
}

bool Term::operator!=(const Term& t2)
{
	return !(*this == t2);
}

void Term::combineFactors()
{
	for (int i = 0; i < factors.size(); i++)
	{
		for (int j = i + 1; j < factors.size(); j++)
		{
			if (factors[j]->type == factors[i]->type && factors[i]->type == Factor::FactorType::Literal)
			{
				auto temp = factors[i];
				factors[i] = factors[i]->multiply(factors[j]);
				delete temp;
				delete factors[j];
				factors.erase(factors.begin() + j);
			}
		}
	}
}

void Term::multiply(const Term& t)
{
	for (auto factor : t.factors)
	{
		factors.push_back(factor->Clone());
	}
	combineFactors();
}

void Term::divide(const Term& t)
{
	auto returnFactor = new Fraction();

	returnFactor->numerator = new Expression(*this);
	returnFactor->denominator = new Expression(t);

	for (auto factor : factors)
		delete factor;

	factors.clear();
	factors.push_back(returnFactor);
}

void Term::divide(const Expression& e)
{
	auto returnFactor = new Fraction();

	returnFactor->numerator = new Expression(*this);
	returnFactor->denominator = new Expression(e);

	for (auto factor : factors)
		delete factor;

	factors.clear();
	factors.push_back(returnFactor);
}

void Term::simplify()
{
	for (int i = 0; i < factors.size() - 1; i++)
	{
		auto result = factors[i]->multiply(factors[i + 1]);
		if (result != nullptr)
		{
			delete factors[i];
			delete factors[i + 1];

			factors.erase(factors.begin() + i, factors.begin() + i + 2);

			factors.insert(factors.begin() + i, result);
		}
	}
}

void Term::multiply(Factor* f)
{
	bool hasMultiplied = false;
	for (auto& factor : factors)
	{
		auto multiplied = factor->multiply(f);
		if (multiplied != nullptr)
		{
			auto temp = factor;
			factor = multiplied;
			delete temp;
			hasMultiplied = true;
			break;
		}

	}
	if (!hasMultiplied)
	{
		factors.push_back(f);
	}

}
