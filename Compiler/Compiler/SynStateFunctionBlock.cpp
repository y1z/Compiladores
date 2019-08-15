#include "stdafx.h"
#include "ErrorFunctions.h"
#include "Utility.h"
#include "GlobolNames.h"
#include "SynStateVar.h"
#include "SynStateFunctionBlock.h"
#include "SynStateExpLog.h"
#include "SynStateIf.h"
#include "SynStateAssigned.h"
#include "SynStatePrint.h"
// to check for Loops 
#include "SynStateFor.h"
//for checking while loops 
#include "SynStateWhile.h"
//! for function block inside other function blocks 
#include "SynStateSubFunctionBlock.h"

namespace Compiler {

	SynStateFunctionBlock::SynStateFunctionBlock(LexAnalyzer * Lex, SyntaxAnalysis * Syn, ISynState * PrevState, SymbolsTable * Symblos, SemanticAnalysis * Semantic, const std::string & Str)
		:ISynState(Lex, Syn, PrevState, Symblos, Semantic), m_FunctionName(Str)
	{
		m_StateName = ("FunctionBlock State");

		m_StateTrasitions =
		{
			{"{",SynStateTransition::FunctionBlock},
			{GNames::k_Var,SynStateTransition::Var} ,
			{GNames::k_Return,SynStateTransition::Return} ,
			{GNames::t_ID,SynStateTransition::ID},
			{"}",SynStateTransition::FunctionBlockEnd},
			{GNames::k_While,SynStateTransition::While},
			{GNames::k_Print, SynStateTransition::Print},
			{GNames::k_If,SynStateTransition::If},
		  {GNames::k_For,SynStateTransition::For},
		};

	}

	SynStateFunctionBlock::~SynStateFunctionBlock()
	{}

	void SynStateFunctionBlock::SelecState(SynStateTransition &UnSelectedState)
	{
		ReadOnlyToken token = mptr_Lex->GetCurrentToken();
		// find-out which state to enter 
		for (auto &States : m_StateTrasitions)
		{
			// check which type of comparison to use 
			if (shouldUseStringComparasion(States.second))
			{
				if (!token->getLex().compare(States.first))
				{
					UnSelectedState = States.second;
					break;
				}
			}
			else
			{
				if (CompareTokenTypes(token, States.first.c_str()))
				{
					UnSelectedState = States.second;
					break;
				}
			}
		}

	}

	bool SynStateFunctionBlock::CheckSyntax()
	{
		bool EndOfFunctionBlock = false;
		ReadOnlyToken token = nullptr;

		if (m_FunctionName.compare("main"))
		{
			MoveAndAssignTokenIndex(mptr_Lex, token);
		}

		token = mptr_Lex->GetCurrentToken();

		// the start of a function-block
		if (!token->getLex().compare("{"))
		{
			MoveAndAssignTokenIndex(mptr_Lex, token);
			// go through the function block 
			while (!EndOfFunctionBlock && token != nullptr)
			{
				SynStateTransition SelectedState = SynStateTransition::Unknown;
				//find out which state to use next 
				SelecState(SelectedState);

				if (SelectedState == SynStateTransition::Var)
				{
					ISynState *ptr_VarState = new SynStateVar(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName);
					ptr_VarState->m_CategorySym = SymbolCategory::local_var;
					ptr_VarState->CheckSyntax();
					delete ptr_VarState;
				}
				//
				else if (SelectedState == SynStateTransition::FunctionBlock)
				{
					ISynState *ptr_FunctionBlock = new SynStateSubFunctionBlock(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName);

					ptr_FunctionBlock->CheckSyntax();

					mptr_Lex->DecreaseTokenIndex();
					delete ptr_FunctionBlock;
				}

				else if (SelectedState == SynStateTransition::If)
				{
					ISynState * IfState = new SynStateIf(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName);

					MoveAndAssignTokenIndex(mptr_Lex, token);
					IfState->CheckSyntax();

					//		mptr_Lex->DecreaseTokenIndex();

					delete IfState;
				}
				// checking for assigned state 
				else if (SelectedState == SynStateTransition::ID)
				{
					Token * Temp_token = mptr_Lex->GetCurrentToken();
					MoveAndAssignTokenIndex(mptr_Lex, token);

					if (!token->getLex().compare("=") || !token->getLex().compare("["))
					{
						ISynState * AssigedState = new SynStateAssigned(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName, Temp_token);
						AssigedState->CheckSyntax();
						delete AssigedState;
					}
					// Checking for Function Call 
					else if (!token->getLex().compare("("))
					{
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

				}

				else	if (SelectedState == SynStateTransition::Return)
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
				else if (SelectedState == SynStateTransition::While)
				{
					ISynState * WhileLoop = new SynStateWhile(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
					MoveAndAssignTokenIndex(mptr_Lex, token);
					WhileLoop->CheckSyntax();
					delete WhileLoop;
				}
				else if (SelectedState == SynStateTransition::For)
				{
					ISynState * ForLoop = new SynStateFor(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
					MoveAndAssignTokenIndex(mptr_Lex, token);
					ForLoop->CheckSyntax();
					delete ForLoop;

				}
				else if (SelectedState == SynStateTransition::Print)
				{
					ISynState *StatePrint = new SynStatePrint(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
					MoveAndAssignTokenIndex(mptr_Lex, token);
					StatePrint->CheckSyntax();
					mptr_Lex->DecreaseTokenIndex();
					delete StatePrint;
				}

				// check for the end of a  function block
				else if (SelectedState == SynStateTransition::FunctionBlockEnd)
				{
					EndOfFunctionBlock = true;

					MoveAndAssignTokenIndex(mptr_Lex, token);
					return true;
				}
				else
				{
					string  ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM("}", token->getLex().c_str());
					mptr_Lex->m_refErrrorsMod->AddSynError(token->getLineNum(), ErrorDesc, "");
					return false;
				}

				if (MoveAndAssignTokenIndex(mptr_Lex, token))
				{ token = mptr_Lex->GetCurrentToken(); }

			}

		}
		else
		{
			string  ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM("{", token->getLex().c_str());
			mptr_Lex->m_refErrrorsMod->AddSynError(token->getLineNum(), ErrorDesc, "");
			return false;
		}
		return false;
	}

}// end namespace