#pragma once
#include "ISynState.h"
namespace Compiler {
	class SynStateElse :
		public ISynState
	{
	public:
		SynStateElse(LexAnalyzer *Lex, SyntaxAnalysis *Syn, 
			ISynState *PrevState, SymbolsTable *Symblos,
			SemanticAnalysis *Semantic, const string &FunctionName);

		~SynStateElse();
	public://functions 
		bool CheckSyntax() override;

	private://variables 
		string m_FunctionName;

	};

}