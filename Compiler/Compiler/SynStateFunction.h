#pragma once
#include "ISynState.h"
namespace Compiler {
	class SynStateFunction : public ISynState
	{
	public:
		SynStateFunction(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic);
		~SynStateFunction();
	public:// funcions 
		bool CheckSyntax()override;
	public:// variables 
		bool isValid = true;
	};

}