#pragma once
#include "ISynState.h"
namespace Compiler {
	class SynStateIf :
		public ISynState
	{
	public:
		SynStateIf(LexAnalyzer *Lex, SyntaxAnalysis *Syn, 
			ISynState *PrevState, 
			SymbolsTable *Symblos, 
			SemanticAnalysis *Semantic,
			string & functionName);
		~SynStateIf();

		bool CheckSyntax();
	private:
		string m_FunctionName;


	};

}