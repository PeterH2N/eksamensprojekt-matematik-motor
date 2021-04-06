// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.

#include "src/expression.h"

#include <iostream>
#include <functional>



int main()
{
    //storedFunctions["sin"] = [](){};

	std::string input = "4/3*a+4=2/3*a";

	Expression expr(input);

	std::cout << expr.solveLinearEquation() << std::endl;

	return 0;
}
