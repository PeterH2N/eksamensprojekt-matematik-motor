// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <regex>

#include "operators.h"

using namespace std;

map<string, Operator*> Operators;
map<string, double> identifiers;

struct Token
{
	enum class TokenType
	{
		Identifier,
		Literal,
		Operator,
		Seperator
	};

	TokenType type;
	string value;

	string TokenTypeString(Token::TokenType type)
	{
		switch (type)
		{
		case Token::TokenType::Identifier:
			return "identifier";
		case Token::TokenType::Literal:
			return "literal";
		case Token::TokenType::Operator:
			return "operator";
		case Token::TokenType::Seperator:
			return "seperator";
		default:
			return "what";
		}
	}

	string printString()
	{
		return "(" + this->TokenTypeString(this->type) + ", " + this->value + ")";
	}
};

template<typename T1, typename T2>
bool mapContainsKey(map<T1, T2> map, T1 key)
{
	for (auto it = map.begin(); it != map.end(); it++)
	{
		if (it->first == key)
			return true;
	}
	return false;
}

 vector<Token> Lexify(string input)
{
	 if (input[input.size() - 1] != ' ')
		 input += " ";
	 vector<Token> Tokens;
	 string sub;
	 size_t firstI = 0;
	 size_t secondI = firstI;

	 while (secondI != -1)
	 {
	 	 Token currentToken;
	 	 
	 	 secondI = input.find(" ", firstI);
	 	 sub = input.substr(firstI, secondI - firstI);
	 	 
	 	 if (sub[0] >= 48 && sub[0] <= 57)
	 	 {
	 	 	 currentToken.type = Token::TokenType::Literal;
	 	 	 currentToken.value = sub;
	 	 	 Tokens.push_back(currentToken);
	 	 }
	 	 else if (mapContainsKey(Operators, sub))
	 	 {
	 	 	 currentToken.type = Token::TokenType::Operator;
	 	 	 currentToken.value = sub;
	 	 	 Tokens.push_back(currentToken);
	 	 }
	 	 else if ((sub[0] >= 65 && sub[0] <= 90) || (sub[0] >= 97 && sub[0] <= 122))
	 	 {
	 	 	 currentToken.type = Token::TokenType::Identifier;
	 	 	 currentToken.value = sub;
	 	 	 Tokens.push_back(currentToken);
	 	 }
	 	 
	 	 firstI = secondI + 1;
	 }
	 return Tokens;
}

 string tokensString(vector<Token> tokens)
 {
	 string returnString = "";
	 for (int i = 0; i < tokens.size(); i++)
	 {
		 returnString += tokens[i].printString();
		 if (i < tokens.size() - 1)
			 returnString += ", ";
	 }
	 return returnString;
 }

 int main()
 {
	 Operators["+"] = new Add();
	 Operators["-"] = new Subtract();
	 Operators["*"] = new Multiply();
	 Operators["/"] = new Divide();
	 Operators["="] = new Equals();

	 string input = "2.5 + x * 6 + 5 = 5.7 * x ";

	 cout << tokensString(Lexify(input)) << endl;
	 return 0;
 }
