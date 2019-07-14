#include "stdafx.h"
#include "SynStateWhile.h"
#include "SynStateExpLog.h"

namespace Compiler {

	SynStateWhile::SynStateWhile(LexAnalyzer * Lex, SyntaxAnalysis * Syn, ISynState * PrevState, SymbolsTable * Symblos, SemanticAnalysis * Semantic, const string & FunctionName)
		:ISynState(Lex, Syn, PrevState, Symblos, Semantic),m_FunctionName(FunctionName)
	{
		m_StateName = " While State ";
	}

	SynStateWhile::~SynStateWhile()
	{}
	// already found the while keyword 
	bool SynStateWhile::CheckSyntax()
	{
		ISynState *ExpLog = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);

		ExpLog->CheckSyntax();

		delete ExpLog;
		return false;
	}

}