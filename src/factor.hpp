# pragma once
#include "token.hpp"

class Expression;
class Literal;
class Fraction;
class Parenthesis;
class Exponential;

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
	Literal();
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
	Factor* multiply(Fraction* f);
	Factor* multiply(Parenthesis* p);
	Factor* multiply(Exponential* p);
	Factor* divide(Literal* l);

};

class Fraction : public Factor
{
public:
	Fraction();
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

	// specific multiply operators
	Factor* multiply(Literal* l);
	Factor* multiply(Fraction* f);
	Factor* multiply(Parenthesis* f);
	Factor* multiply(Exponential* f);

	// specific divide operators
	Factor* divide(Literal* l);
	Factor* divide(Fraction* f);
	Factor* divide(Parenthesis* f);
	Factor* divide(Exponential* f);

};

class Parenthesis : public Factor
{
public:
	Parenthesis();	
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

	// specific multiply operators
	Factor* multiply(Literal* l);
	Factor* multiply(Fraction* f);
	Factor* multiply(Parenthesis* f);
	Factor* multiply(Exponential* f);
	// specific divide operators
	Factor* divide(Literal* l);
	Factor* divide(Fraction* f);
	Factor* divide(Parenthesis* f);
	Factor* divide(Exponential* f);
};

class Exponential : public Factor
{
public:
	Exponential();
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

	// specific multiply operators
	Factor* multiply(Literal* l);
	Factor* multiply(Fraction* f);
	Factor* multiply(Parenthesis* f);
	Factor* multiply(Exponential* f);
	// specific divide operators
	Factor* divide(Literal* l);
	Factor* divide(Fraction* f);
	Factor* divide(Parenthesis* f);
	Factor* divide(Exponential* f);
};
