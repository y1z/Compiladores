#pragma once
#include "ISynState.h"

#include "StateTransitionEnums.h"

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

		void SelecState(SynStateTransition &State);

		bool CheckSyntax()override;


	  std::map<string, SynStateTransition> m_StateTrasitions;
	public:// variables 
		string m_FunctionName;
	};
}