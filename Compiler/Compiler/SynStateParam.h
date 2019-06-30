#pragma once
#include "ISynState.h"
#include "SynStateVar.h"
#include <vector>

namespace Compiler {
	class SynStateParam :
		public ISynState
	{
	public:
		SynStateParam(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic);
		SynStateParam(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic,string functionName);
		~SynStateParam();

		bool CheckSyntax()override;
		std::vector<LocalNode> GetNodes();
		string m_Type;
	private:
		//! the var state already contains logic needed for parsing 
		SynStateVar * mptr_VarState = nullptr;
		//! this is to make sure that the syntax is still 
		bool IsValid = true;

		string m_FuntionName;
		std::vector<LocalNode> m_Nodes;
	};
}
