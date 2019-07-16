#pragma once
#include "ISynState.h"
#include "StateTransitionEnums.h"
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

		int8_t CheckTransition(const Token* token);


	private:// variables 
		string m_FunctionName;
		std::vector<std::pair<string, SynStateTransition>> m_StateTransition;
	};

}