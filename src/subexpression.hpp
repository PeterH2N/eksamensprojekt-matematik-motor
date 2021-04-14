# pragma once
#include "token.hpp"

class Expression;

class SubExpression
{
public:
	SubExpression(){}
	virtual ~SubExpression() = 0;
protected:
	enum class SubExpressionType : char
	{
		LiteralTerm,
		Exponential,
		Fraction,
		Parenthesis,
		Invalid,
	};

	SubExpression(SubExpressionType _type)
		: type(_type) {}

	SubExpressionType type = SubExpressionType::Invalid;
public:
	virtual std::vector<Token> getTokens() = 0;

	virtual SubExpressionType getType() = 0;

protected:
	// literalTerm
	std::vector<Token> tokens;

	// fraction
	Expression* numerator = nullptr;
	Expression* denominator = nullptr;

	// parenthesis
	SubExpression* scalar = nullptr;
	Expression* expression = nullptr;

	// exponents
	SubExpression* base = nullptr;
	SubExpression* exponent = nullptr;

	virtual SubExpression* multiply(SubExpression* s) = 0;

};

class LiteralTerm : public SubExpression
{
public:
	LiteralTerm(){}

	LiteralTerm(std::vector<Token> _tokens);

	bool sign = true;

	std::vector<Token> getTokens();

	SubExpressionType getType();

	SubExpression* multiply(SubExpression* s);
};

class Fraction : public SubExpression
{
public:
	Fraction(std::vector<Token> _tokens)
		: SubExpression(SubExpression::SubExpressionType::Fraction) {}

	~Fraction()
	{
		delete numerator;
		delete denominator;
	}

	std::vector<Token> getTokens();

	SubExpressionType getType();
};

class Parenthesis : public SubExpression
{
public:
	Parenthesis(std::vector<Token> _tokens)
		: SubExpression(SubExpression::SubExpressionType::Parenthesis) {}

	~Parenthesis()
	{
		delete scalar;
		delete expression;
	}

	std::vector<Token> getTokens();

	SubExpressionType getType();
};

class Exponential : public SubExpression
{
	Exponential(std::vector<Token> _tokens)
		: SubExpression(SubExpression::SubExpressionType::Exponential) {}

	~Exponential()
	{
		delete base;
		delete exponent;
	}

	std::vector<Token> getTokens();

	SubExpressionType getType();
};