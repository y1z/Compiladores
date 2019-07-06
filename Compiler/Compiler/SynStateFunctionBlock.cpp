#include "stdafx.h"
#include "SynStateFunctionBlock.h"

namespace Compiler {
	SynStateFunctionBlock::SynStateFunctionBlock(LexAnalyzer * Lex, SyntaxAnalysis * Syn, ISynState * PrevState, SymbolsTable * Symblos, SemanticAnalysis * Semantic, const std::string & Str)
		:ISynState(Lex, Syn, PrevState, Symblos, Semantic)
	{
		m_StateName = ("FunctionBlock");
	}

	SynStateFunctionBlock::~SynStateFunctionBlock()
	{}

	bool SynStateFunctionBlock::CheckSyntax()
	{
		return false;
	}


}