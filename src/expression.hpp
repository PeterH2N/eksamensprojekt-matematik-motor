#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "token.hpp"

class Expression
{
public:

	struct SubExprIdentifier
	{
		enum class SubExprType : int
		{
			Invalid,
			Term,
			Parenthesis,
			Numerator,
			Denominator,
			Function,
		};
		SubExprIdentifier(){}
		SubExprIdentifier(std::pair<int, int>, SubExprType);

		std::pair<int, int> indices;

		SubExprType type = SubExprType::Invalid;
	};

	Expression();
	Expression(std::string);
	Expression(std::vector<Token>);
	Expression(const Expression&);

	std::vector<Token> tokens;

	std::vector<SubExprIdentifier> identifiers;

	std::pair<int, int> getParenthesesIndices(int offset = 0);

	void lexify(std::string);

	void identify();

	Expression subExprFromIndices(std::pair<int,int> indices) const;

	Expression replaceByIndices(Expression replacement, std::pair<int,int> indices) const;

	Expression calculated() const;

	Expression multiplyByFactor(const Expression& factor);

	Expression simplyfy();

	Expression solveLinearEquation();

	Expression isolateIdentifier(std::string identifier);

	std::string printString() const;

	friend std::ostream& operator<<(std::ostream& os, const Expression& t);
};

#endif EXPRESSION_H