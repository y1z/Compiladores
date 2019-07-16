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

#include "SynStateWhile.h"
#include "SynStateFor.h"

Compiler::SynStateSubFunctionBlock::
SynStateSubFunctionBlock(LexAnalyzer * Lex, SyntaxAnalysis * Syn, ISynState * PrevState, SymbolsTable * Symblos, SemanticAnalysis * Semantic, const string & FunctionName)
	:ISynState(Lex, Syn, PrevState, Symblos, Semantic), m_FunctionName(FunctionName)
{
	m_StateName = " Sub Function Block State ";


	m_StateTransition = { {GNames::t_ID,SynStateTransition::ID}
		, {GNames::k_Return,SynStateTransition::Return}
		, {GNames::k_If, SynStateTransition::If}
		, {GNames::k_While,SynStateTransition::While}
		,{GNames::k_For,SynStateTransition::For}
		, {}
	};

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
		int8_t State = -1;
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

			///	mptr_Lex->DecreaseTokenIndex();

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
		// checking for the if statement 
		else if (!token->getLex().compare("if"))
		{
			ISynState * IfState = new SynStateIf(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName);

			MoveAndAssignTokenIndex(mptr_Lex, token);
			IfState->CheckSyntax();

			delete IfState;
		}
		else if (!token->getLex().compare("while"))
		{
			ISynState * WhileLoop = new SynStateWhile(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
			MoveAndAssignTokenIndex(mptr_Lex, token);
			WhileLoop->CheckSyntax();
			delete WhileLoop;
		}
		else if (!token->getLex().compare("for"))
		{
			ISynState * ForLoop = new SynStateFor(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
			MoveAndAssignTokenIndex(mptr_Lex, token);
			ForLoop->CheckSyntax();
			delete ForLoop;
		}
		else if (CompareTokenTypes(token,GNames::t_ID))
		{
			MoveAndAssignTokenIndex(mptr_Lex, token);

			if (!token->getLex().compare("=") || !token->getLex().compare("["))
			{
				ISynState * AssigedState = new SynStateAssigned(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName);
				AssigedState->CheckSyntax();
				delete AssigedState;
			}

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

int8_t
Compiler::SynStateSubFunctionBlock::CheckTransition(const Token* token)
{
	SynStateTransition Result = SynStateTransition::Unknown;

	if(CompareTokenTypes(token,GNames::t_ID))
	{
		Result = SynStateTransition::ID;
		return static_cast<int8_t>(Result);
	}

	for(const auto &State : m_StateTransition)
	{
		if(!token->getLex().compare(State.first))
		{
			Result = State.second;
			break;
		}
	}

	return static_cast<int8_t>(Result);
}
