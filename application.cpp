// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.

#include "expression.hpp"

#include <iostream>
#include <functional>



int main()
{
	std::string input = "(-2)^2";

	Expression f(lexify(input));

	std::cout << getStringFromTokens(f.getTokens()) << std::endl;

	return 0;
}
