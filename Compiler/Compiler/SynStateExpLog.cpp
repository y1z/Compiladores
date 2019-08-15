#include "stdafx.h"
#include "Utility.h"
#include "ErrorFunctions.h"
#include "SemanticAnalysis.h"
#include "SynStateExpLog.h"
#include "Token.h"

using namespace std::string_literals;

Compiler::SynStateExpLog::SynStateExpLog
(
	LexAnalyzer * Lex,
	SyntaxAnalysis * Syn,
	ISynState * PrevState,
	SymbolsTable * Symblos,
	SemanticAnalysis * Semantic,
	const std::string &FunctionName,
	const string &Delimiter
)
	:ISynState(Lex, Syn, PrevState, Symblos, Semantic), IsNegation(false), m_CountParenthesis(0), m_Delimiter(Delimiter)
{
	m_StateName = ("Expression Log State");
	m_FunctionName = FunctionName;

	Token *Temp = Lex->GetCurrentToken();

	m_Data.m_LineNum = Temp->getLineNum();
	m_Data.m_FunctionName = m_FunctionName;

	IsDone = false;
}

Compiler::SynStateExpLog::SynStateExpLog(LexAnalyzer * Lex, SyntaxAnalysis * Syn,
	ISynState * PrevState, SymbolsTable * Symblos,
	SemanticAnalysis * Semantic, const std::string & FunctionName,
	const Token * tokenFromAssigedState)
	:ISynState(Lex, Syn, PrevState, Symblos, Semantic), IsNegation(false), m_CountParenthesis(0), m_FunctionName(FunctionName)
{
	m_Data.mptr_tokens.emplace_back(tokenFromAssigedState);
	m_Data.m_LineNum = tokenFromAssigedState->getLineNum();
	m_Data.m_FunctionName = FunctionName;
}

Compiler::SynStateExpLog::~SynStateExpLog()
{}

bool Compiler::SynStateExpLog::CheckSyntax()
{
	ReadOnlyToken Tok = mptr_Lex->GetCurrentToken();

	auto checkForNegation = [&](ReadOnlyToken &token)
	{
		IsNegation = CheckForNagation(token);
		// move forward if you find a '!' aka negation 
		(IsNegation) ? MoveAndAssignTokenIndex(mptr_Lex, token) : 0;
	};

	checkForNegation(Tok);

	ProcessTerm();

	Tok = mptr_Lex->GetCurrentToken();

	if (!IsDone)
	{
		// checkin for end of file 
		if (Tok != nullptr)
		{
			// cheking for operator 
			if (CompareTokenTypes(Tok, "RELATIONAL_OPERATOR")
				|| CompareTokenTypes(Tok, "LOGICAL_OPERATOR")
				|| CompareTokenTypes(Tok, "ARITHMETIC_OPERATOR")
				|| CompareTokenTypes(Tok, "DIMENSION_OPERATOR"))
			{
				m_Data.m_SymbolsToCheck = "~"s + Tok->getLex();
				m_Data.m_IndexSymbolToUpdate.emplace_back(m_Data.mptr_tokens.size());
				m_Data.mptr_tokens.emplace_back(Tok);

				MoveAndAssignTokenIndex(mptr_Lex, Tok);
				checkForNegation(Tok);
				Tok = mptr_Lex->GetCurrentToken();
				ProcessTerm();
			}
			//create new logical expression just so i separate the different logical expressions
			else	if (!Tok->getLex().compare(","))
			{
				MoveAndAssignTokenIndex(mptr_Lex, Tok);
				ISynState *ptr_NexExpLog = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
				bool Result = ptr_NexExpLog->CheckSyntax();
				this->IsDone = true;
				delete ptr_NexExpLog;
				return Result;
			}
			//check if all parenthesis are close 
			else if (m_CountParenthesis == 0)
			{
				if (!m_Data.mptr_tokens.empty())
				{
					mptr_Semantic->AddExplog(m_Data);
					m_Data.mptr_tokens.clear();
				}
				IsDone = true;
				return true;
			}

			else if (m_CountParenthesis > 0)
			{
				string ErrorDesc = ErrorFuncs::SYN_EXPO_EXPECTED(m_Parenthesis);
				mptr_Lex->m_refErrrorsMod->AddSynError(Tok->getLineNum(), ErrorDesc, "");
				IsDone = true;
				return false;
			}
		}
	}
	else
	{
		if (!m_Data.mptr_tokens.empty())
		{
			mptr_Semantic->AddExplog(m_Data);
			m_Data.mptr_tokens.clear();
		}
		return true;
	}

	return false;
}

bool Compiler::SynStateExpLog::CheckForFunctionCall()
{
	ReadOnlyToken Tok = nullptr;
	MoveAndAssignTokenIndex(mptr_Lex, Tok);
	if (!Tok->getLex().compare("("))
	{
		ISynState *NewEpresstion = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);

		NewEpresstion->CheckSyntax();

		delete NewEpresstion;
		Tok = mptr_Lex->GetCurrentToken();
		if (!Tok->getLex().compare(")"))
		{
			MoveAndAssignTokenIndex(mptr_Lex, Tok);
			///TODO FIX 
			if (!Tok->getLex().compare(";") || !Tok->getLex().compare(")"))
			{
				return true;
			}
			else
			{
				string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(";", Tok->getLex().c_str());
				mptr_Lex->m_refErrrorsMod->AddSynError(Tok->getLineNum(), ErrorDesc, "");
				return false;
			}

		}
		else
		{
			string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM("(", Tok->getLex().c_str());
			mptr_Lex->m_refErrrorsMod->AddSynError(Tok->getLineNum(), ErrorDesc, "");
			return false;
		}

	}// check for ';'

	return false;
}

bool Compiler::SynStateExpLog::CheckForNagation(const Token * Tok)
{
	if (!Tok->getLex().compare("!"))
	{
		m_Data.mptr_tokens.emplace_back(Tok);
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
			m_Data.mptr_tokens.emplace_back(Tok);
			MoveAndAssignTokenIndex(mptr_Lex, Tok);
			this->CheckSyntax();
		}
		//checking for constants 
		else if (CompareTokenTypes(Tok, "STRING_CONSTANT")
			|| CompareTokenTypes(Tok, "INT_NUMBER")
			|| CompareTokenTypes(Tok, "FLOAT_NUMBER")
			|| CompareTokenTypes(Tok, "LOGICAL_CONSTANT"))
		{
			m_Data.mptr_tokens.emplace_back(Tok);
			MoveAndAssignTokenIndex(mptr_Lex, Tok);
			CheckSyntax();
		}
		//
		else if (CompareTokenTypes(Tok, "ID"))
		{
			m_Data.mptr_tokens.emplace_back(Tok);
			if (CheckForFunctionCall())
			{
				return;
			}
			else
			{
				this->CheckSyntax();
			}
		}
		// checking for the closing of parenthesis
		else if (!Tok->getLex().compare(")"))
		{
			// this is for when the state is inside a function 
			if (m_CountParenthesis >= 1)
			{
				this->m_Parenthesis.emplace_back(')');
				this->m_CountParenthesis--;
				m_Data.mptr_tokens.emplace_back(Tok);
				MoveAndAssignTokenIndex(mptr_Lex, Tok);
				this->CheckSyntax();
			}
		}
	}
}