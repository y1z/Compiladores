#include "stdafx.h"
#include "SemanticAnalysis.h"
#include "SynStateExpLog.h"


Compiler::SynStateExpLog::SynStateExpLog(
	LexAnalyzer * Lex, 
	SyntaxAnalysis * Syn, 
	ISynState * PrevState, 
	SymbolsTable * Symblos, 
	SemanticAnalysis * Semantic,
	const std::string &FunctionName)
	:ISynState(Lex, Syn, PrevState, Symblos, Semantic), IsNegation(false), m_ParenthesisLevel(0) 
{
	m_StateName = ("Expression Log");
}

Compiler::SynStateExpLog::~SynStateExpLog()
{}

bool Compiler::SynStateExpLog::CheckSyntax()
{
	ReadOnlyToken Tok = mptr_Lex->GetCurrentToken();
	IsNegation = CheckForNagation(Tok);
	// move forward if you find a '!' aka negation 
	(IsNegation) ? MoveAndAssignTokenIndex(mptr_Lex, Tok) : 0;

	ProcessTerm();

	if (Tok != nullptr)
	{
		if(CompareTokenTypes(Tok, "RELATIONAL_OPERATOR") 
			|| CompareTokenTypes(Tok, "LOGICAL_OPERATOR")
			|| CompareTokenTypes(Tok, "ARITHMETIC_OPERATOR")
			|| CompareTokenTypes(Tok, "DIMENSION_OPERATOR"))
		{
			this->CheckSyntax();
		}

	}

	if (m_ParenthesisLevel == 0)
	{
		mptr_Semantic->AddExplog(m_ExpressionTokens,)

		return true;
	}

	return false;
}

bool Compiler::SynStateExpLog::CheckForFunctionCall()
{
	return false;
}

bool Compiler::SynStateExpLog::CheckForNagation(ReadOnlyToken & Tok)
{
	if (!Tok->getLex().compare("!"))
	{
		m_ExpressionTokens.emplace_back(Tok);
		return true;
	}
	return false;
}

void Compiler::SynStateExpLog::ProcessTerm()
{
	ReadOnlyToken Tok = nullptr;
	Tok = mptr_Lex->GetCurrentToken();

	if (!Tok->getLex().compare("("))
	{
		this->m_ParenthesisLevel++;
		MoveAndAssignTokenIndex(mptr_Lex, Tok);
		this->CheckSyntax();
	}
	//checking for constants
	else if (CompareTokenTypes(Tok, "STRING_CONSTANT")
		|| CompareTokenTypes(Tok, "INT_NUMBER")
		|| CompareTokenTypes(Tok, "FLOAT_NUMBER")
		|| CompareTokenTypes(Tok, "LOGICAL_CONSTANT"))
	{
		m_ExpressionTokens.emplace_back(Tok);
	}
	//
	else if (CompareTokenTypes(Tok, "ID"))
	{
		m_ExpressionTokens.emplace_back(Tok);
	}
	// check for function call 
	else if (CheckForFunctionCall())
	{

	}
	else if (!Tok->getLex().compare(")"))
	{ this->m_ParenthesisLevel--; }

}