#pragma once
#include <string>
/*! used to represent tokens */
using namespace System;

namespace Compiler {
	
	enum Token_Type
	{
		UNDEFINED = 0,
		ID,
		INT
	};
};


class Token
{
public:
	Token(std::string Lex, Compiler::Token_Type Token, int lineNum);
	Token();
  ~Token();
public:// functions 
	std::string getLex() const;
	Compiler::Token_Type getType() const;
	int getLineNum() const;

private:
	std::string m_Lex;
	int m_lineNumber;
	Compiler::Token_Type m_token;
};
