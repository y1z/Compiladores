#include "stdafx.h"
#include "SynStateFor.h"
#include "SynStateAssigned.h"
#include  "SynStateExpLog.h"
#include "SynStateIncremenAndDecrement.h"
#include "SynStateSubFunctionBlock.h"
#include "ErrorFunctions.h"

using namespace std::string_literals;
namespace Compiler {

	SynStateFor::SynStateFor(LexAnalyzer *Lex, SyntaxAnalysis *Syn, ISynState *PrevState, SymbolsTable *Symblos, SemanticAnalysis *Semantic, const string &FunctionName)
		:ISynState(Lex, Syn, PrevState, Symblos, Semantic), m_FunctionName(FunctionName)
	{
		m_StateName = " For State ";
	}


	SynStateFor::~SynStateFor()
	{}

	// already found the 'for' keyword 
	bool SynStateFor::CheckSyntax()
	{
		string ExpectedSequence = "(a;e;i){";

		auto MakeError = [&](string Current, ReadOnlyToken tok) -> bool
		{
			string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(Current.c_str(), tok->getLex().c_str());
			mptr_Lex->m_refErrrorsMod->AddSynError(tok->getLineNum(), ErrorDesc, "");
			return false;
		};

		for (std::size_t i = 0; i < ExpectedSequence.size(); ++i)
		{
			ReadOnlyToken token = mptr_Lex->GetCurrentToken();
			string CurrentChar{ ExpectedSequence[i] };
			if (ExpectedSequence[i] == 'a' || ExpectedSequence[i] == 'e' || ExpectedSequence[i] == 'i' || ExpectedSequence[i] == '{')
			{
				ISynState *State = nullptr;
				switch (ExpectedSequence[i])
				{
				case('a'):// checking for assignment 
					if (CompareTokenTypes(token, GNames::t_ID))
					{
						MoveAndAssignTokenIndex(mptr_Lex, token);
						State = new SynStateAssigned(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
						State->CheckSyntax();
						delete State;
						mptr_Lex->DecreaseTokenIndex();
					}
					else
					{ return MakeError(GNames::t_ID, token); }
					break;

				case('e'):// check for logical expression 
					State = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
					State->CheckSyntax();
					delete State;
					mptr_Lex->DecreaseTokenIndex();
					break;

				case('i'):// check for increment or decrement
					if (!token->getLex().compare(GNames::k_Inc) || !token->getLex().compare(GNames::k_Dec))
					{
						State = new SynStateIncremenAndDecrement(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
						MoveAndAssignTokenIndex(mptr_Lex, token);
						State->CheckSyntax();
						delete State;
					}
					else
					{
						MakeError("'"s + GNames::k_Inc + "'"s + " | "s + "'"s + GNames::k_Dec + "'"s, token);
					}
					break;
					 
				case('{'):
					State = new SynStateSubFunctionBlock(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
					State->CheckSyntax();
					delete State;
					token = mptr_Lex->GetCurrentToken();
					break;
				}
			}
			else// check to see if char match up 
			{
				if (!token->getLex().compare(CurrentChar))
				{
					MoveAndAssignTokenIndex(mptr_Lex, token);
					continue;
				}
				else
				{
					string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(CurrentChar.c_str(), token->getLex().c_str());
					mptr_Lex->m_refErrrorsMod->AddSynError(token->getLineNum(), ErrorDesc, "");
					return false;
				}
			}
			// move forward 
			MoveAndAssignTokenIndex(mptr_Lex, token);
		}
		return true;
	}

}