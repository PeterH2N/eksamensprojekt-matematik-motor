// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.

#include "expression.hpp"

#include <iostream>
#include <functional>



int main()
{
	std::string input = "(-2)^2";

	Expression e(lexify("2*x^2+(2+x)"));
	Expression e2(lexify("(1+x)/(x^2)"));

	e.multiply(e2);

	std::cout << getStringFromTokens(e.getTokens()) << std::endl;
	e.simplify();
	std::cout << getStringFromTokens(e.getTokens()) << std::endl;



	return 0;
}
