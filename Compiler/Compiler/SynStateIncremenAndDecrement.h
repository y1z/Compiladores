#pragma once
#include "ISynState.h"
namespace Compiler {

	class SynStateIncremenAndDecrement :
		public ISynState
	{
	public:
		SynStateIncremenAndDecrement(
			LexAnalyzer *Lex, SyntaxAnalysis *Syn,
			ISynState *PrevState, SymbolsTable *Symblos,
			SemanticAnalysis *Semantic, const string &FunctionName);

		~SynStateIncremenAndDecrement();
	public:
		bool CheckSyntax()override;
	private:
		string m_FunctionName;
	};

}