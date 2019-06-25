#pragma once
#include "ISynState.h"

namespace Compiler {
	class SynStateProgram : public ISynState
	{
	public:
		SynStateProgram(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos);
		~SynStateProgram();
	public:// functions
		bool CheckSyntax() override;
	public:
		bool isGlobal = true;
		
	};

}