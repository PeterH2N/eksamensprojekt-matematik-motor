#pragma once

class Operator
{
public:
	Operator() {}
};


class Add : public Operator
{
	double operation(double a, double b)
	{
		return a + b;
	}
};

class Subtract : public Operator
{
	double operation(double a, double b)
	{
		return a - b;
	}
};

class Multiply : public Operator
{
	double operation(double a, double b)
	{
		return a * b;
	}
};

class Divide : public Operator
{
	double operation(double a, double b)
	{
		return a / b;
	}
};

class Equals : public Operator
{
	double operation(double a, double b)
	{
		return 0;
	}
};