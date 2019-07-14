#pragma once
#include "ISynState.h"
namespace Compiler {
	class SynStatePrint :
		public ISynState
	{
	public:
		SynStatePrint(LexAnalyzer *Lex, SyntaxAnalysis *Syn, ISynState *PrevState, SymbolsTable *Symblos, SemanticAnalysis *Semantic,string FunctionName);
		~SynStatePrint();
	public:

		bool CheckSyntax() override;

	private:
		string m_FunctionName;
	};

}