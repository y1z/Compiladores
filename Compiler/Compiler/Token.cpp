#include "stdafx.h"
#include "Token.h"

Token::Token(const std::string &Lex, Compiler::Token_Type Token, int LineNum)
	:m_Lex(Lex),m_token(Token),m_lineNumber(LineNum)
{}

Token::Token()
{}

Token::~Token()
{}

std::string Token::getLex() const
{
	return m_Lex;
}

Compiler::Token_Type Token::getType() const
{
	return m_token;
}

int Token::getLineNum() const
{
	return m_lineNumber;
}
