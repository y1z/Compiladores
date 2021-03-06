#pragma once
#include "ISynState.h"

namespace Compiler {
	class SynStateProgram : public ISynState
	{
	public:
		SynStateProgram(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic);
		~SynStateProgram();
	public:// functions
		bool CheckSyntax() override;
	public:
		bool isGlobal = true;
		bool isMainFound = false;
	};

}