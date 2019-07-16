#pragma once
#include "ISynState.h"
namespace Compiler {

	class SynStateFor :
		public ISynState
	{
	public:
		SynStateFor(
			LexAnalyzer *Lex, SyntaxAnalysis *Syn, 
			ISynState *PrevState, SymbolsTable *Symblos, 
			SemanticAnalysis *Semantic,const string &FunctionName);

		~SynStateFor();
	public:
		bool CheckSyntax()override;

	private:
		string m_FunctionName;
	};

}