// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

char operators[] = {'+', '-', '*', '/', '^', '='};
char seperators[] = {';'};
map<string, double> identifiers;

template<typename T, int N>
bool arrayContains(T(&array)[N], T key)
{
    for (int i = 0; i < N; i++)
    {
        if (key == array[i])
            return true;
    }
    return false;
}

struct Token
{
    enum TokenType : int
	{
		Identifier,
		Literal,
		Operator,
        Seperator,
        Invalid
	};

	TokenType type;
	string value;

	string TokenTypeString(Token::TokenType type)
	{
		switch (type)
		{
        case (int)Token::TokenType::Identifier:
			return "identifier";
        case (int)Token::TokenType::Literal:
			return "literal";
        case (int)Token::TokenType::Operator:
			return "operator";
        case (int)Token::TokenType::Seperator:
			return "seperator";
		default:
            return "invalid";
		}
	}

	string printString()
	{
		return "(" + this->TokenTypeString(this->type) + ", " + this->value + ")";
	}
};

Token::TokenType getTypeFromChar(char c)
{
    if (arrayContains(operators, c))
        return Token::TokenType::Operator;
    else if (c >= 48 && c <= 57)
        return Token::TokenType::Literal;
    else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        return Token::TokenType::Identifier;
    else if (arrayContains(seperators, c))
        return Token::TokenType::Seperator;
    else
        return Token::TokenType::Invalid;
}

 vector<Token> Lexify(string input)
{
	 vector<Token> Tokens;
     char currentChar;
     Token::TokenType currentType, prevType;
     string buffer;

     prevType = Token::TokenType::Invalid;

     for (size_t i = 0; i < input.size(); i++)
     {
         currentChar = input[i];
         currentType = getTypeFromChar(currentChar);



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

	 string input = "2.5 + test = 5.7";

	 cout << tokensString(Lexify(input)) << endl;
	 return 0;
 }
