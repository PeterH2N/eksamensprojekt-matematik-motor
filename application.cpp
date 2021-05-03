// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.

#include "expression.hpp"

#include <iostream>
#include <functional>



int main()
{
	std::string input = "(-2)^2";

    Fraction t(lexify("a/b"));
    Fraction l(lexify("b/c"));


	std::cout << getStringFromTokens(t.divide(&l)->getTokens()) << std::endl;


	return 0;
}
