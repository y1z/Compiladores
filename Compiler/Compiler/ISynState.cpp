#include "stdafx.h"
#include "ISynState.h"
#include "LexAnalyzer.h"
#include "SyntaxAnalysis.h"
#include "SymbolsTable.h"

Compiler::ISynState::ISynState()
{
	this->m_StateName = "Unknown";
}

Compiler::ISynState::ISynState(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic)
{
	this->mptr_Lex = ptr_Lex;
	this->mptr_Syn = ptr_Syn;
	this->mptr_PrevState = ptr_PrevState;
	this->mptr_SymbolsTable = ptr_Symblos;
	this->mptr_Semantic = ptr_Semantic;
}

Compiler::ISynState::~ISynState()
{
	PrintToConsole(" State Exit : {0} ",m_StateName);
}

//void Compiler::ISynState::InitState(LexAnalyzer * ptr_Lex, SyntaxAnalysis * ptr_Syn, ISynState * ptr_PrevState, SymbolsTable * ptr_Symblos)
//{
//	mptr_Lex = ptr_Lex;
//	mptr_Syn = ptr_Syn;
//	mptr_PrevState = ptr_PrevState;
//	mptr_SymbolsTable = ptr_Symblos;
//}

