#include "expression.hpp"

Expression::Expression(std::vector<Token> _tokens)
{
	organize(_tokens);
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

void Expression::organize(std::vector<Token> tokens)
{
	// split the tokens into terms, skipping over each parenthesis

	std::vector<std::vector<Token>> termsTokens;

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
		else if (tokens[i].value == "+" || tokens[i].value == "-")
		{
			nextTermIndex = i;
			std::vector<Token> termTokens;
			if (lastTermIndex == nextTermIndex)
				termTokens = std::vector<Token>({ tokens[lastTermIndex] });
			else
				termTokens = std::vector<Token>(&tokens[lastTermIndex], &tokens[nextTermIndex]);
			terms.push_back(new Term(termTokens));

			lastTermIndex = nextTermIndex;
		}
		else  if (i == tokens.size() - 1)
		{
			std::vector<Token> termTokens = std::vector<Token>(&tokens[lastTermIndex], tokens.end()._Ptr);
			terms.push_back(new Term(termTokens));
		}
	}

}
