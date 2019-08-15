#pragma once
#include "ISynState.h"
namespace Compiler {

	class SynStateAssigned : public ISynState
	{
	public:
		SynStateAssigned(
			LexAnalyzer *Lex, SyntaxAnalysis *Syn, 
			ISynState *PrevState, SymbolsTable *Symblos, 
			SemanticAnalysis *Semantic, const string &FunctionName, const Token *token);
		~SynStateAssigned();

	public:
		// ! checks the syntax for the assigned action
		bool CheckSyntax();
		// ! for checking an array
		bool CheckArray();

		string	m_FunctionName;
		const Token * m_IdToken = nullptr;
		bool IsDone;
	};

}