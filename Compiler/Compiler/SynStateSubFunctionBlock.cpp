#include "stdafx.h"
#include "SynStateSubFunctionBlock.h"
#include "ErrorFunctions.h"
#include "GlobolNames.h"
#include "SynStateVar.h"
#include "SynStateFunctionBlock.h"
#include "SynStateExpLog.h"
#include "SynStateIf.h"
#include "SynStateAssigned.h"
#include "SynStatePrint.h"

#include <memory>

Compiler::SynStateSubFunctionBlock::
SynStateSubFunctionBlock(LexAnalyzer * Lex, SyntaxAnalysis * Syn, ISynState * PrevState, SymbolsTable * Symblos, SemanticAnalysis * Semantic, const string & FunctionName)
	:ISynState(Lex, Syn, PrevState, Symblos, Semantic), m_FunctionName(FunctionName)
{
	m_StateName = " Sub Function Block State ";

	m_StateTransitions = { {GNames::t_ID,0}, {GNames::k_Return,1},{GNames::k_Else,2}, {GNames::k_While,3} };
}


Compiler::SynStateSubFunctionBlock::
~SynStateSubFunctionBlock()
{}

bool Compiler::SynStateSubFunctionBlock::
CheckSyntax()
{
	bool IsDone = false;
	ReadOnlyToken token = mptr_Lex->GetCurrentToken();

	while (!IsDone)
	{
		int State = -1;
		MoveAndAssignTokenIndex(mptr_Lex, token);

		if (CompareTokenTypes(token, GNames::t_ID))
		{
			State = 0;
		}

		if (State == 0)
		{
			MoveAndAssignTokenIndex(mptr_Lex, token);
			if (!token->getLex().compare("=") || !token->getLex().compare("["))
			{
				ISynState * ptr_Exp = new SynStateAssigned(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);

				ptr_Exp->CheckSyntax();

				delete ptr_Exp;
			}

		}
		else if (!token->getLex().compare("if"))
		{
			ISynState * IfState = new SynStateIf(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName);

			MoveAndAssignTokenIndex(mptr_Lex, token);
			IfState->CheckSyntax();

			mptr_Lex->DecreaseTokenIndex();

			delete IfState;
		}
		else	if (!token->getLex().compare("return"))
		{
			MoveAndAssignTokenIndex(mptr_Lex, token);

			ISynState *ptr_Expresstion = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
			ptr_Expresstion->CheckSyntax();

			token = mptr_Lex->GetCurrentToken();
			if (!token->getLex().compare(";"))
			{
				delete ptr_Expresstion;
			}
			else
			{
				string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(";", token->getLex().c_str());
				mptr_Lex->m_refErrrorsMod->AddSynError(token->getLineNum(), ErrorDesc, "");
				delete ptr_Expresstion;
			}
		}
		else if (!token->getLex().compare(GNames::k_Print))
		{
			ISynState *StatePrint = new SynStatePrint(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
			MoveAndAssignTokenIndex(mptr_Lex, token);
			StatePrint->CheckSyntax();
			mptr_Lex->DecreaseTokenIndex();
			delete StatePrint;
		}
		else if (!token->getLex().compare("{"))
		{
			ISynState *ptr_FunctionBlock = new SynStateSubFunctionBlock(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName);

			ptr_FunctionBlock->CheckSyntax();

			mptr_Lex->DecreaseTokenIndex();
			delete ptr_FunctionBlock;
		}
		// check for the end of a  function block
		else if (!token->getLex().compare("}"))
		{
			MoveAndAssignTokenIndex(mptr_Lex, token);
			return true;
		}
		else
		{
			string  ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM("}", token->getLex().c_str());
			mptr_Lex->m_refErrrorsMod->AddSynError(token->getLineNum(), ErrorDesc, "");
			return false;
		}

	}

	return false;
}
