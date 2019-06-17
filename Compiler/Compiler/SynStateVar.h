#pragma once
#include "ISynState.h"

namespace Compiler {

	class SynStateVar : public ISynState
	{
	public: 
		SynStateVar(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos);
		~SynStateVar();
		bool CheckSyntax() override;
	};

}