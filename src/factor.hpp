# pragma once
#include "token.hpp"

class Expression;

class Factor
{
public:
	Factor() {};
	virtual ~Factor() = 0;

	enum class FactorType : char
	{
		Literal,
		Exponential,
		Fraction,
		Parenthesis,
		Invalid,
	};
protected:
	Factor(FactorType _type)
		: type(_type) {}

	FactorType type = FactorType::Invalid;
public:
	friend Factor* getFactorPointerFromType(std::vector<Token> tokens, FactorType type);

	virtual std::vector<Token> getTokens() = 0;

	virtual FactorType getType() = 0;

protected:

	virtual Factor* multiply(Factor* s) = 0;

	virtual Factor* divide(Factor* s) = 0;
};

class Literal : public Factor
{
public:
	Literal(){}

	Literal(std::vector<Token> _tokens);

	double value = 1;

	std::vector<std::pair<std::string, double>> identifiers;

	std::vector<Token> getTokens();

	FactorType getType();

	Factor* multiply(Factor* s);

	Factor* divide(Factor* s);
};

class Fraction : public Factor
{
public:
	Fraction(std::vector<Token> tokens);

	~Fraction()
	{
		delete numerator;
		delete denominator;
	}

	Expression* numerator = nullptr;
	Expression* denominator = nullptr;

	std::vector<Token> getTokens();

	FactorType getType();

	Factor* multiply(Factor* s);

	Factor* divide(Factor* s);
};

class Parenthesis : public Factor
{
public:
	Parenthesis(std::vector<Token> tokens);

	~Parenthesis()
	{
		delete expression;
	}
	Expression* expression = nullptr;

	std::vector<Token> getTokens();

	FactorType getType();

	Factor* multiply(Factor* s);

	Factor* divide(Factor* s);
};

class Exponential : public Factor
{
public:
	Exponential(std::vector<Token> tokens);

	~Exponential()
	{
		delete base;
		delete exponent;
	}

	Expression* base = nullptr;
	Expression* exponent = nullptr;

	std::vector<Token> getTokens();

	FactorType getType();

	Factor* multiply(Factor* s);

	Factor* divide(Factor* s);
};