#include "stdafx.h"
#include "Token.h"

Token::Token(std::string Lex, Compiler::Token_Type Token, int lineNum)
{}

Token::Token()
{}

Token::~Token()
{}

std::string Token::getLex() const
{
	return std::string();
}

Compiler::Token_Type Token::getType() const
{
	return Compiler::Token_Type();
}

int Token::getLineNum() const
{
	return 0;
}
