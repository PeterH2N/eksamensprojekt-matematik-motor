#include "expression.hpp"
#include <iterator>

Expression::Expression(std::vector<Token> _tokens)
{
	organize(_tokens);
}

Expression::Expression(const Expression& e)
{
	for (auto term : e.terms)
	{
		terms.push_back(new Term(*term));
	}
}

Expression::~Expression()
{
	for (auto term : terms)
		delete term;
}

std::vector<Token> Expression::getTokens()
{
	std::vector<Token> returnVector;

	for (int i = 0; i < terms.size(); i++)
	{
		auto tempTokens = terms[i]->getTokens();
		if (i == 0 && tempTokens[0].value == "+")
			tempTokens.erase(tempTokens.begin());
		returnVector.insert(returnVector.end(), tempTokens.begin(), tempTokens.end());
	}
	return returnVector;
}

bool Expression::operator==(const Expression& e2)
{
	if (terms.size() != e2.terms.size())
		return false;

	// same as term, the expressions will be equal even if theyre out of order
	for (int i = 0; i < terms.size(); i++)
	{
		bool exists = false;
		for (int j = 0; j < terms.size(); j++)
		{
			if (*e2.terms[i] == *terms[j])
				exists = true;
		}
		if (!exists)
			return false;
	}

	return true;
}

bool Expression::operator!=(const Expression& e2)
{
	return !(*this == e2);
}

void Expression::multiply(Factor* f)
{
	for (auto& term : terms)
	{
		term->multiply(f);
	}
}

void Expression::multiply(const Expression& e)
{
	Expression copy(*this);

	for (auto& term : terms)
	{
		delete term;
	}
	terms.clear();

	for (auto& eterm : e.terms)
	{
		for (auto& cterm : copy.terms)
		{
			Term* temp= new Term(*cterm);
			temp->multiply(*eterm);
			terms.push_back(temp);
		}
	}
}

void Expression::organize(std::vector<Token> tokens)
{
	// split the tokens into terms, skipping over each parenthesis

	int lastTermIndex = 0;
	int nextTermIndex = 0;

	for (int i = 0; i < tokens.size(); i++)
	{
		// skipping over parenthesis
		if (tokens[i].value == "(")
		{
			int nextParenthesisIndex = getParenthesisIndices(tokens, i).second;
			i = nextParenthesisIndex - 1;
		}
		else if ((tokens[i].value == "+" || tokens[i].value == "-") && i != 0)
		{
			nextTermIndex = i;
			std::vector<Token> termTokens;
			if (lastTermIndex == nextTermIndex)
            {
                termTokens.clear();
                termTokens.push_back(tokens[lastTermIndex]);
            }
			else
				termTokens = std::vector<Token>(&tokens[lastTermIndex], &tokens[nextTermIndex]);
			terms.push_back(new Term(termTokens));

			lastTermIndex = nextTermIndex;
		}
		else  if (i == tokens.size() - 1)
		{
            std::vector<Token> termTokens = std::vector<Token>(&tokens[lastTermIndex], &tokens[tokens.size() - 1]);
			terms.push_back(new Term(termTokens));
		}
	}

}
