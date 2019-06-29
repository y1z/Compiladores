#include "stdafx.h"
#include "SynStateProgram.h"
#include "SynStateVar.h"
#include "SynStateFunction.h"
#include "GlobolNames.h"
#include "ErrorFunctions.h"


Compiler::SynStateProgram::SynStateProgram(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic)
	:ISynState(ptr_Lex, ptr_Syn, ptr_PrevState, ptr_Symblos,ptr_Semantic)
{
	m_StateName = "Syn State : Program";
}

Compiler::SynStateProgram::~SynStateProgram()
{
	PrintToConsole("State Destructor: {0}", std::string("State Program"));
	if(!isMainFound)
	{
		string ErrorDesc = "Error: expected '<main>', but EOF was reached";
		const Token *Temp = mptr_Lex->GetCurrentToken();

		mptr_Lex->m_refErrrorsMod->AddSynError(Temp->getLineNum(), ErrorDesc, "");
	}
}

bool Compiler::SynStateProgram::CheckSyntax()
{
	bool Continue = true;
	while (Continue)
	{
	const Token *ptr_Tok = mptr_Lex->GetCurrentToken();
		// check if the token is correct
		if (!ptr_Tok->getLex().compare("var"))
		{
			ISynState * VarState = new SynStateVar(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable,mptr_Semantic);
			// if not in a function the var is global 
			VarState->m_CategorySym = SymbolCategory::global_var;
			VarState->CheckSyntax();
			delete VarState;
		}
		// this is the function state 
		else if (!ptr_Tok->getLex().compare(g_Names::k_Func))
		{
			ISynState * FunctionState = new SynStateFunction(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable,mptr_Semantic);
			FunctionState->m_CategorySym = SymbolCategory::function;
			FunctionState->CheckSyntax();
			delete FunctionState;
		}

		Continue = mptr_Lex->AdvanceTokenIndex();
	}

	return false;
}
