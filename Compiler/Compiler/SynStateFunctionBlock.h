#pragma once
#include "ISynState.h"
namespace Compiler {
	class SynStateFunctionBlock :
		public ISynState
	{
	public:// constructors
		SynStateFunctionBlock(LexAnalyzer *Lex, 
			SyntaxAnalysis *Syn, 
			ISynState *PrevState, 
			SymbolsTable *Symblos, 
			SemanticAnalysis *Semantic, 
			const std::string &Str);

		~SynStateFunctionBlock();

		bool CheckSyntax()override;

	  std::map<string,int> m_StateTrasitions;
	public:// variables 
		string m_FunctionName;
	};
}