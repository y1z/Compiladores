#include "stdafx.h"
#include "SynStateVar.h"

Compiler::SynStateVar::SynStateVar(LexAnalyzer * ptr_Lex, SyntaxAnalysis * ptr_Syn, ISynState * ptr_PrevState, SymbolsTable * ptr_Symblos)
	:ISynState(ptr_Lex,ptr_Syn,ptr_PrevState,ptr_Symblos)
{}

Compiler::SynStateVar::~SynStateVar()
{}

bool Compiler::SynStateVar::CheckSyntax()
{
	return false;
}
