// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.

#include "expression.hpp"

#include <iostream>
#include <functional>



int main()
{
	std::string input = "(-2)^2";

	Literal t(lexify("2*x^3"));
	Literal l(lexify("3*x^3"));

	std::cout << getStringFromTokens(t.divide(&l)->getTokens()) << std::endl;


	return 0;
}
