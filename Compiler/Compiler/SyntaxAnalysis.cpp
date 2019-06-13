#include "stdafx.h"
#include "SyntaxAnalysis.h"


namespace Compiler {


	SyntaxAnalysis::SyntaxAnalysis(LexAnalyzer * ptr_Lex, ErrorsModule ^ Error, SymblosTable * ptr_Table)
		:mptr_Lex(ptr_Lex), mref_ErrorMod(Error), mptr_Table(ptr_Table)
	{}

	SyntaxAnalysis::~SyntaxAnalysis()
	{}

	void SyntaxAnalysis::checkSyntax()
	{
	
	}

}