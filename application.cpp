// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.

#include "src/expression.h"

#include <iostream>
#include <functional>



int main()
{
    //storedFunctions["sin"] = [](){};

	std::string input = "2*(0-6)+(5*2)";

	Expression expr(input);

	std::cout << expr.calculated() << std::endl;

	return 0;
}
