#include "stdafx.h"
#include "SynStateFunction.h"
#include "SynStateVar.h"

Compiler::SynStateFunction::SynStateFunction(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic)
	:ISynState(ptr_Lex, ptr_Syn, ptr_PrevState, mptr_SymbolsTable,mptr_Semantic)
{}

Compiler::SynStateFunction::~SynStateFunction()
{}

bool Compiler::SynStateFunction::CheckSyntax()
{
	mptr_Lex->AdvanceTokenIndex();
	ReadOnlyToken Tok = mptr_Lex->GetCurrentToken();
	// check params 
	if (!Tok->getLex().compare("("))
	{
		SynStateVar* VarState = new SynStateVar(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable,mptr_Semantic);
		isValid = VarState->CheckForValidType();
		delete VarState;
	}


	return false;
}
