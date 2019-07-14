#pragma once
#include "ISynState.h"

namespace Compiler {

	class SynStateWhile :
		public ISynState
	{
	public:
		SynStateWhile(LexAnalyzer *Lex, SyntaxAnalysis *Syn, ISynState *PrevState, SymbolsTable *Symblos, SemanticAnalysis *Semantic, const string &FunctionName);
		~SynStateWhile();
	public:// functions 
		bool CheckSyntax();
	private:
		string m_FunctionName;
	};

}