// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.

#include "expression.hpp"

#include <iostream>
#include <functional>



int main()
{
	std::string input = "(-2)^2";

    Expression t(lexify("2"));
    Expression l(lexify("x"));

	t.multiply(l);

	std::cout << getStringFromTokens(t.getTokens()) << std::endl;


	return 0;
}
