#pragma once
#include "Token.h"
#include "SymbolsTable.h"

using ReadOnlyToken = const Token *;

namespace Compiler {

	class LexAnalyzer;
	class SyntaxAnalysis;
	class SymbolsTable;//SymbolsTable
	class SemanticAnalysis;
}

namespace Compiler {

	public class ISynState
	{
	public:
		ISynState();
		ISynState(LexAnalyzer *Lex, SyntaxAnalysis *Syn, ISynState *PrevState, SymbolsTable *Symblos, SemanticAnalysis *Semantic);
		virtual ~ISynState();
	public:
		virtual	bool CheckSyntax() = 0;
	public:
		LexAnalyzer * mptr_Lex = nullptr;
		SyntaxAnalysis * mptr_Syn = nullptr;
		ISynState * mptr_PrevState = nullptr;
		SymbolsTable * mptr_SymbolsTable = nullptr;
		SemanticAnalysis *mptr_Semantic = nullptr;

		std::string m_StateName;
		SymbolCategory m_CategorySym = SymbolCategory::global_var;
	};

}