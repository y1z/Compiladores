#pragma once
#include "ISynState.h"

namespace Compiler {
	class SynStateSubFunctionBlock :
		public ISynState
	{
	public:// constructor 
		SynStateSubFunctionBlock(
			LexAnalyzer *Lex, 
			SyntaxAnalysis *Syn, 
			ISynState *PrevState, 
			SymbolsTable *Symblos, 
			SemanticAnalysis *Semantic,
			const string &FunctionName);

		~SynStateSubFunctionBlock();
	public:// functions 

		bool CheckSyntax();
	private:// variables 
		string m_FunctionName;
		std::vector<std::pair<string, int>> m_StateTransition;
	};

}