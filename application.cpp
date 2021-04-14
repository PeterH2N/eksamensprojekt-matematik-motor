// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.

#include "expression.hpp"

#include <iostream>
#include <functional>



int main()
{
	

	std::string input = "x^2+3*x+1=0";

	SubExpression* t = new LiteralTerm(lexify(input));

	for (auto token : t->getTokens())
	std::cout << token << " ";

	return 0;
}
