#pragma once
#include "ISynState.h"
namespace Compiler {
	class SynStateFunctionBlock :
		public ISynState
	{
	public:
		SynStateFunctionBlock(LexAnalyzer *Lex, 
			SyntaxAnalysis *Syn, 
			ISynState *PrevState, 
			SymbolsTable *Symblos, 
			SemanticAnalysis *Semantic, 
			const std::string &Str);

		~SynStateFunctionBlock();

		bool CheckSyntax()override;
	};
}