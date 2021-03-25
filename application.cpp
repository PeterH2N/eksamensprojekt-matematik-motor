// Eksamensprojekt-mathengine.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

char operators[] = { '+', '-', '*', '/', '^', '=', '(', ')', ':' };
char seperators[] = { ';' };
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

template<typename T1, typename T2>
bool mapContainsKey(map<T1, T2> map, T1 key)
{
	for (auto it = map.begin(); it != map.end(); it++)
		if (it->first == key)
			return true;
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
		Function,
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
		case (int)Token::TokenType::Function:
			return "function";
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
	else if ((c >= 48 && c <= 57) || c == '.')
		return Token::TokenType::Literal;
	else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95)
		return Token::TokenType::Identifier;
	else if (arrayContains(seperators, c))
		return Token::TokenType::Seperator;
	else
		return Token::TokenType::Invalid;
}



map< string, function<Token(vector<Token>)>> storedFunctions;

vector<Token> Lexify(string input)
{
	input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

	vector<Token> tokens;
	Token currentToken;
	char currentChar;
	Token::TokenType currentType = Token::TokenType::Invalid, prevType;
	string buffer;
	bool hasADecimal = false;

	currentChar = input[0];
	prevType = getTypeFromChar(currentChar);

	buffer = currentChar;

	for (size_t i = 1; i < input.size(); i++)
	{
		currentChar = input[i];
		currentType = getTypeFromChar(currentChar);



		if ((currentType == Token::TokenType::Literal && prevType == Token::TokenType::Literal) || (prevType == Token::TokenType::Literal && currentChar == '.' && !hasADecimal))
		{
			hasADecimal = true;
			buffer += currentChar;
		}
		else if (prevType == Token::TokenType::Identifier && (currentType == Token::TokenType::Identifier || currentType == Token::TokenType::Literal))
		{
			buffer += currentChar;
		}
		else if (currentType != prevType)
		{
			if (mapContainsKey(storedFunctions, buffer))
			{
				prevType = Token::TokenType::Function;
			}
			currentToken.type = prevType;
			currentToken.value = buffer;
			tokens.push_back(currentToken);
			buffer = currentChar;
			prevType = currentType;
		}
		else if (currentType == Token::TokenType::Invalid)
		{
			cout << "Invalid character in expression at character " + i + 1 << endl;
			return {};
		}

	}
	currentToken.type = currentType;
	currentToken.value = buffer;
	tokens.push_back(currentToken);

	return tokens;
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

Token Sin(vector<Token> args)
{
	return Token();
}

int main()
{
	storedFunctions["sin"] = Sin;

	string input = "sin(x)=5";

	cout << tokensString(Lexify(input)) << endl;
	return 0;
}
