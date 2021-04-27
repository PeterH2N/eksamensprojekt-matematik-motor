// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.

#include "expression.hpp"

#include <iostream>
#include <functional>



int main()
{
	std::string input = "(-2)^2";

	Expression t(lexify("2*x^2+3*x"));
	Expression l(lexify("x+2"));

	t.multiply(l);

	std::cout << getStringFromTokens(t.getTokens()) << std::endl;


	return 0;
}
