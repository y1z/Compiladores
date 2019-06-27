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
		ISynState(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic);
		virtual ~ISynState();
	public:
		virtual	bool CheckSyntax() = 0;
		/*! this is basically the constructor for the state had troubles with the actual ctor*/
	//	virtual void InitState(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos);
	//	virtual void InitState(ISynState * ptr_OtherState);
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