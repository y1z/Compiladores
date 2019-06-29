#pragma once
#include "ISynState.h"
#include "SynStateVar.h"

namespace Compiler {
	class SynStateParam :
		public ISynState
	{
	public:
		SynStateParam(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic);
		~SynStateParam();

		bool CheckSyntax()override;
	private:
		//! the var state already contains logic needed for parsing 
		SynStateVar * mptr_VarState = nullptr;
		//! this is to make sure that the syntax is still 
		bool IsValid = true;
	};
}
