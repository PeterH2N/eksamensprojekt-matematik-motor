# pragma once
#include "token.hpp"

class Expression;

class Factor
{
public:
	enum class FactorType : char
	{
		Literal,
		Exponential,
		Fraction,
		Parenthesis,
		Invalid,
	};
	static Factor* Create(const std::vector<Token> tokens, const FactorType& type);
	virtual Factor* Clone() = 0;
	virtual ~Factor() = 0;

	Factor(FactorType _type)
		: type(_type) {}

	FactorType type = FactorType::Invalid;

	virtual std::vector<Token> getTokens() = 0;

	virtual FactorType getType() = 0;

	virtual bool operator==(Factor* f2) = 0;

	virtual bool operator!=(Factor* f2) = 0;

	virtual Factor* multiply(Factor* s) = 0;

	virtual Factor* divide(Factor* s) = 0;
};

class Literal : public Factor
{
public:
	Literal(const Literal& l);
	Literal(const std::vector<Token>& _tokens);

	Factor* Clone();
private:

	double value = 1;

    std::vector<std::pair<std::string, double> > identifiers;

public:

	std::vector<Token> getTokens();

	FactorType getType();

	Factor* multiply(Factor* s);

	Factor* divide(Factor* s);

	bool operator==(Factor* f2);
	bool operator!=(Factor* f2);

	// specific operations
	Factor* multiply(Literal* l);
	Factor* divide(Literal* l);

};

class Fraction : public Factor
{
public:
	Fraction(const std::vector<Token>& tokens);
	Fraction(const Fraction& f);
	~Fraction();

	Factor* Clone();

	Expression* numerator = nullptr;
	Expression* denominator = nullptr;

	std::vector<Token> getTokens();

	FactorType getType();

	Factor* multiply(Factor* s);

	Factor* divide(Factor* s);

	bool operator==(Factor* f2);
	bool operator!=(Factor* f2);
};

class Parenthesis : public Factor
{
public:
	Parenthesis(const std::vector<Token>& tokens);
	Parenthesis(const Parenthesis& p);
	~Parenthesis();

	Factor* Clone();

	Expression* expression = nullptr;

	std::vector<Token> getTokens();

	FactorType getType();

	Factor* multiply(Factor* s);

	Factor* divide(Factor* s);

	bool operator==(Factor* f2);
	bool operator!=(Factor* f2);
};

class Exponential : public Factor
{
public:
	Exponential(const std::vector<Token>& tokens);
	Exponential(const Exponential& e);
	~Exponential();

	Factor* Clone();

	Expression* base = nullptr;
	Expression* exponent = nullptr;

	std::vector<Token> getTokens();

	FactorType getType();

	Factor* multiply(Factor* s);

	Factor* divide(Factor* s);

	bool operator==(Factor* f2);
	bool operator!=(Factor* f2);
};
