#include "stdafx.h"
#include "ErrorFunctions.h"
#include "SemanticAnalysis.h"
#include "SynStateExpLog.h"
#include "Token.h"


Compiler::SynStateExpLog::SynStateExpLog(
	LexAnalyzer * Lex,
	SyntaxAnalysis * Syn,
	ISynState * PrevState,
	SymbolsTable * Symblos,
	SemanticAnalysis * Semantic,
	const std::string &FunctionName)
	:ISynState(Lex, Syn, PrevState, Symblos, Semantic), IsNegation(false), m_CountParenthesis(0)
{
	m_StateName = ("Expression Log");
	m_FunctionName = FunctionName;
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

	Tok = mptr_Lex->GetCurrentToken();

	if (Tok != nullptr)
	{
		if (CompareTokenTypes(Tok, "RELATIONAL_OPERATOR")
			|| CompareTokenTypes(Tok, "LOGICAL_OPERATOR")
			|| CompareTokenTypes(Tok, "ARITHMETIC_OPERATOR")
			|| CompareTokenTypes(Tok, "DIMENSION_OPERATOR"))
		{
			this->CheckSyntax();
		}

	}

	if (!Tok->getLex().compare(","))
	{
		MoveAndAssignTokenIndex(mptr_Lex, Tok);
		return this->CheckSyntax();
	}

	if (m_CountParenthesis == 0)
	{
		mptr_Semantic->AddExplog(m_ExpressionTokens, m_FunctionName);

		return true;
	}

	else if (m_CountParenthesis > 0)
	{
		string ErrorDesc = ErrorFuncs::SYN_EXPO_EXPECTED(m_Parenthesis);
		mptr_Lex->m_refErrrorsMod->AddSynError(Tok->getLineNum(), ErrorDesc, "");
	}

	return false;
}

bool Compiler::SynStateExpLog::CheckForFunctionCall()
{
	ReadOnlyToken Tok = nullptr;
	MoveAndAssignTokenIndex(mptr_Lex, Tok);
	if (!Tok->getLex().compare("("))
	{
		return this->CheckSyntax();
	}


	return false;
}

bool Compiler::SynStateExpLog::CheckForNagation(const Token * Tok)
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
	const Token* Tok = nullptr;
	Tok = mptr_Lex->GetCurrentToken();

	if (Tok != nullptr)
	{
		if (!Tok->getLex().compare("("))
		{
			this->m_CountParenthesis++;
			this->m_Parenthesis.emplace_back('(');
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
			MoveAndAssignTokenIndex(mptr_Lex, Tok);
			CheckSyntax();
		}
		//
		else if (CompareTokenTypes(Tok, "ID"))
		{
			m_ExpressionTokens.emplace_back(Tok);
			CheckForFunctionCall();
		}
		// check for function call 
		else if (!Tok->getLex().compare(")"))
		{
			this->m_Parenthesis.emplace_back(')');
			this->m_CountParenthesis--;
			this->CheckSyntax();
		}

	}
	

}