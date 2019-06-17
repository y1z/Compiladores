#include "stdafx.h"
#include "SynStateProgram.h"

Compiler::SynStateProgram::SynStateProgram(LexAnalyzer * ptr_Lex, SyntaxAnalysis * ptr_Syn, ISynState * ptr_PrevState, SymbolsTable * ptr_Symblos)
	:ISynState(ptr_Lex, ptr_Syn, ptr_PrevState, ptr_Symblos)
{}

Compiler::SynStateProgram::~SynStateProgram()
{
	PrintToConsole("State Destructor: {0}", std::string("State Program"));
}

bool Compiler::SynStateProgram::CheckSyntax()
{
	const Token *ptr_Tok = mptr_Lex->GetPeekToken();

	if (!ptr_Tok->getLex().compare("var"))
	{

	}

	return false;
}
