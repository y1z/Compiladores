#include "stdafx.h"
#include "SynStateProgram.h"
#include "SynStateVar.h"
#include "SynStateFunction.h"
#include "GlobolNames.h"


Compiler::SynStateProgram::SynStateProgram(LexAnalyzer * ptr_Lex, SyntaxAnalysis * ptr_Syn, ISynState * ptr_PrevState, SymbolsTable * ptr_Symblos)
	:ISynState(ptr_Lex, ptr_Syn, ptr_PrevState, ptr_Symblos)
{}

Compiler::SynStateProgram::~SynStateProgram()
{
	PrintToConsole("State Destructor: {0}", std::string("State Program"));
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
			ISynState * VarState = new SynStateVar(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable);
			// if not in a function the var is global 
			VarState->m_CategorySym = SymbolCategory::global_var;
			VarState->CheckSyntax();
			delete VarState;
		}
		// this is the function state 
		else if (!ptr_Tok->getLex().compare(g_Names::k_Func))
		{
			ISynState * FunctionState = new SynStateFunction(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable);



			delete FunctionState;
		}

		Continue = mptr_Lex->AdvanceTokenIndex();
	}

	return false;
}
