#include "..\subexpression.hpp"

LiteralTerm::LiteralTerm(std::vector<Token> _tokens)
	: SubExpression(SubExpressionType::LiteralTerm)
{
	tokens = _tokens;
	sign = tokens[0].value == "-" ? false : true;
	if (!sign)
		tokens.erase(tokens.begin());
}

std::vector<Token> LiteralTerm::getTokens()
{
	auto returnTokens = tokens;
	Token signToken = sign ? Token(Token::TokenType::Operator, "+") : Token(Token::TokenType::Operator, "-");
	returnTokens.insert(returnTokens.begin(), signToken);
	return returnTokens;
}

SubExpression::SubExpressionType LiteralTerm::getType()
{
	return type;
}

SubExpression* LiteralTerm::multiply(SubExpression* s)
{
	return nullptr;
}
