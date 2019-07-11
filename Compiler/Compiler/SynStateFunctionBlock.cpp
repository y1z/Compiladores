#include "stdafx.h"
#include "ErrorFunctions.h"
#include "GlobolNames.h"
#include "SynStateVar.h"
#include "SynStateFunctionBlock.h"
#include "SynStateExpLog.h"
#include "SynStateIf.h"

namespace Compiler {



	SynStateFunctionBlock::SynStateFunctionBlock(LexAnalyzer * Lex, SyntaxAnalysis * Syn, ISynState * PrevState, SymbolsTable * Symblos, SemanticAnalysis * Semantic, const std::string & Str)
		:ISynState(Lex, Syn, PrevState, Symblos, Semantic), m_FunctionName(Str)
	{
		m_StateName = ("FunctionBlock");
	}

	SynStateFunctionBlock::~SynStateFunctionBlock()
	{}

	bool SynStateFunctionBlock::CheckSyntax()
	{
		bool EndOfFunctionBlock = false;
		ReadOnlyToken token = nullptr;

		if (m_FunctionName.compare("main"))
		{
			MoveAndAssignTokenIndex(mptr_Lex, token);
		}

		token = mptr_Lex->GetCurrentToken();

		m_StateTrasitions = { {"{",0} ,{GNames::k_Var,1} ,{GNames::k_Return,2}  };

		if (!token->getLex().compare("{"))
		{
			MoveAndAssignTokenIndex(mptr_Lex, token);
			// go through the function block 
			while (!EndOfFunctionBlock && token != nullptr)
			{
				/// implament later 
				//auto Transition = m_StateTrasitions.find(token->getLex());
				if (!token->getLex().compare("var"))
				{
					ISynState *ptr_VarState = new SynStateVar(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName);
					ptr_VarState->m_CategorySym = SymbolCategory::local_var;
					ptr_VarState->CheckSyntax();
					delete ptr_VarState;
				}
				// recursion 
				else if (!token->getLex().compare("{"))
				{
					ISynState *ptr_FunctionBlock = new SynStateFunctionBlock(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName);
					ptr_FunctionBlock->CheckSyntax();

					delete ptr_FunctionBlock;
				}
				else if (!token->getLex().compare("if"))
				{
					ISynState * IfState = new SynStateIf(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName);

					MoveAndAssignTokenIndex(mptr_Lex, token);
					IfState->CheckSyntax();

				//MoveAndAssignTokenIndex(mptr_Lex, token);
				//
				//ISynState *ptr_Expresstion = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
				//ptr_Expresstion->CheckSyntax();
				//MoveAndAssignTokenIndex(mptr_Lex, token);
				//if (!token->getLex().compare(";"))
				//{
				//
				//}
				//
					//delete ptr_Expresstion;
					token = mptr_Lex->GetCurrentToken();

					delete IfState;
				}
				/// TODO FINSH THIS 
				else	if (!token->getLex().compare("return"))
				{
					MoveAndAssignTokenIndex(mptr_Lex, token);

					ISynState *ptr_Expresstion = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
					ptr_Expresstion->CheckSyntax();
					//if (CompareTokenTypes(token, "INT_NUMBER") || CompareTokenTypes(token, "FLOAT_NUMBER") || CompareTokenTypes(token, "LOGICAL_CONSTANT"))
					//{
					//	MoveAndAssignTokenIndex(mptr_Lex, token);
					//	if (!token->getLex().compare(GNames::d_LineEnd))
					//	{
					//		MoveAndAssignTokenIndex(mptr_Lex, token);
					//	}
					//	
					//}
					delete ptr_Expresstion;
				}
				// check for the end of a  function block
				else if (!token->getLex().compare("}"))
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

				MoveAndAssignTokenIndex(mptr_Lex, token);
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