#pragma once
#include <string>
using namespace System;


namespace Compiler {
	// all possible token
	enum Token_Type
	{
		UNDEFINED = 0,
		ID,
		INT_NUMBER,
		FLOAT_NUMBER,
		STRING_CONSTANT,
		LOGICAL_CONSTANT,
		RELATIONAL_OPERATOR,
		LOGICAL_OPERATOR,
		GROUPING_OPERATOR,
		UNARY_LOGICAL_OPERATOR,
		ASSIGN_OPERATOR,
		ARITHMETIC_OPERATOR,
		DIMENSION_OPERATOR,
		SEPARATOR,
		KEYWORD
	};
};

/*! used to represent tokens */
class Token
{
public:
	Token(const std::string &Lex, Compiler::Token_Type Token, int lineNum);
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