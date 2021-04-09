// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.

#include "src/expression.hpp"

#include <iostream>
#include <functional>



int main()
{
    //storedFunctions["sin"] = "HI";

	std::string input = "2*x+5=5/3*x+7";

	Expression expr(input);

	std::cout << expr.solveLinearEquation() << std::endl;

	return 0;
}
