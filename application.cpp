// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.

#include "src/expression.h"

#include <iostream>
#include <functional>



int main()
{
	storedFunctions["sin"] = [](std::vector<Token> args) {return Token();};

	std::string input = "sin(x)";

	Expression expr(input);

	std::cout << expr << std::endl;
	return 0;
}
