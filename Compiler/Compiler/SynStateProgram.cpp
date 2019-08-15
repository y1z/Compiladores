#include "stdafx.h"
#include "SynStateProgram.h"
#include "SynStateVar.h"
#include "SynStateFunction.h"
#include "GlobolNames.h"
#include "Utility.h"
#include "ErrorFunctions.h"
#include "StateTransitionEnums.h"


Compiler::SynStateProgram::SynStateProgram(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic)
	:ISynState(ptr_Lex, ptr_Syn, ptr_PrevState, ptr_Symblos, ptr_Semantic)
{
	m_StateName = " State Program ";
}

Compiler::SynStateProgram::~SynStateProgram()
{
	PrintToConsole("State Destructor: {0}", std::string("State Program"));
}

bool Compiler::SynStateProgram::CheckSyntax()
{

	std::map<std::string, SynStateTransition> ValidWord = {
		{ GNames::k_Var,SynStateTransition::Var},
		{GNames::k_Main,SynStateTransition::Main} ,
		{GNames::k_Func,SynStateTransition::Function} };

	bool KeepGoing = true;
	while (KeepGoing)
	{
		SynStateTransition StateSelected = (SynStateTransition::Unknown);

		const Token *ptr_Tok = mptr_Lex->GetCurrentToken();

		if (ValidWord.find(ptr_Tok->getLex()) != ValidWord.end())
		{
			auto Temp = ValidWord.find(ptr_Tok->getLex());
			StateSelected = Temp->second;
		}

		if (StateSelected == SynStateTransition::Var)
		{			//var keyword
			ISynState * VarState = new SynStateVar(this->mptr_Lex, this->mptr_Syn, this, this->mptr_SymbolsTable, this->mptr_Semantic);
			// if not in a function the var is global 
			VarState->m_CategorySym = SymbolCategory::global_var;
			VarState->CheckSyntax();
			MoveAndAssignTokenIndex(mptr_Lex, ptr_Tok);
			delete VarState;
			KeepGoing = mptr_Lex->AdvanceTokenIndex();
			mptr_Lex->DecreaseTokenIndex();
		}
		// main keyword
		else	if (StateSelected == SynStateTransition::Main)
		{
			this->isMainFound = true;
			ISynState * FunctionState = new SynStateFunction(this->mptr_Lex, this->mptr_Syn, this, this->mptr_SymbolsTable, this->mptr_Semantic);
			FunctionState->m_CategorySym = SymbolCategory::function;
			FunctionState->CheckSyntax();

			KeepGoing = mptr_Lex->AdvanceTokenIndex();
			ptr_Tok = mptr_Lex->GetCurrentToken();
			delete FunctionState;
			return true;
		}
		//function keyword 
		else	if (StateSelected == SynStateTransition::Function)
		{
			ISynState * FunctionState = new SynStateFunction(this->mptr_Lex, this->mptr_Syn, this, this->mptr_SymbolsTable, this->mptr_Semantic);
			FunctionState->m_CategorySym = SymbolCategory::function;

			FunctionState->CheckSyntax();
			ptr_Tok = mptr_Lex->GetCurrentToken();
			delete FunctionState;
			continue;
		}
		else if (StateSelected == SynStateTransition::Unknown)
		{
			if(isMainFound == false)
			{
				Token *tok = mptr_Lex->GetCurrentToken();
				string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM("main", tok->getLex().c_str());
				mptr_Lex->m_refErrrorsMod->AddSynError(tok->getLineNum(), ErrorDesc, "");
				return false;
			}

		}

	}
	return isMainFound;
}
