#include "stdafx.h"
#include "ErrorFunctions.h"
#include "SynStateIf.h"
#include "SynStateExpLog.h"
namespace Compiler {

	SynStateIf::SynStateIf()
	{}

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
		ISynState * ExpLog = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic,m_FunctionName);

		ExpLog->CheckSyntax();
		Token * tok = mptr_Lex->GetCurrentToken();
		if (!tok->getLex().compare(";"))
		{
			delete ExpLog;
			return true;
		}
		else
		{
			delete ExpLog;
			string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(";", tok->getLex().c_str());
			mptr_Lex->m_refErrrorsMod->AddSynError(tok->getLineNum(), ErrorDesc, "");
			return false;
		}

		delete ExpLog;

		return false;
	}








}