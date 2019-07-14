#include "stdafx.h"
#include "ErrorFunctions.h"
#include "SynStateIf.h"
#include "SynStateExpLog.h"
namespace Compiler {

	SynStateIf::SynStateIf(LexAnalyzer * Lex, SyntaxAnalysis * Syn, ISynState * PrevState, SymbolsTable * Symblos, SemanticAnalysis * Semantic, string & functionName)
		:ISynState(Lex, Syn, PrevState, Symblos, Semantic),m_FunctionName(functionName)
	{
		m_StateName = "IF State";
	}

	SynStateIf::~SynStateIf()
	{}
	// Already found the 'if' keyword 
	bool SynStateIf::CheckSyntax()
	{
		ISynState * ExpLog = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic,m_FunctionName,"{");

		ExpLog->CheckSyntax();

		ReadOnlyToken token = mptr_Lex->GetCurrentToken();

		if (!token->getLex().compare("{"))
		{
			delete ExpLog;
			return true;
		}
		else
		{
			string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM("{", token->getLex().c_str());
			mptr_Lex->m_refErrrorsMod->AddSynError(token->getLineNum(), ErrorDesc, "");
			delete ExpLog;
			return true;
		}

		delete ExpLog;

		return false;
	}
}