#include "stdafx.h"
#include "SynStateAssigned.h"
#include "ErrorFunctions.h"
#include "SynStateExpLog.h"

namespace Compiler {

	SynStateAssigned::SynStateAssigned(LexAnalyzer * Lex, SyntaxAnalysis * Syn, ISynState * PrevState, SymbolsTable * Symblos, SemanticAnalysis * Semantic, const string & FunctionName)
		:ISynState(Lex, Syn, PrevState, Symblos, Semantic), m_FunctionName(FunctionName)
	{
		m_StateName = ("Assigned State");
		IsDone = false;
	}

	SynStateAssigned::~SynStateAssigned()
	{}
	// already found the id 
	bool SynStateAssigned::CheckSyntax()
	{
		ReadOnlyToken	Tok = mptr_Lex->GetCurrentToken();
		if (!Tok->getLex().compare("["))
		{
			CheckArray();
			MoveAndAssignTokenIndex(mptr_Lex, Tok);
		}
		else if (!Tok->getLex().compare("="))
		{
			MoveAndAssignTokenIndex(mptr_Lex, Tok);
		}
		// checking for regular assignment
		ISynState *ExpLog = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);

		ExpLog->CheckSyntax();

		delete ExpLog;

		Tok = mptr_Lex->GetCurrentToken();
		if (Tok->getLex().compare(";"))
		{
			return true;
		}


		return false;
	}

	bool SynStateAssigned::CheckArray()
	{
		ReadOnlyToken Tok = mptr_Lex->GetCurrentToken();
		/// checking for arrays assignment
		if (!Tok->getLex().compare("["))
		{
			ISynState *Expression = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
			// check for error with the logical expression
			if (!Expression->CheckSyntax())
			{
				delete Expression;
				return false;
			}
			else if (mptr_Lex->GetCurrentToken()->getLex().compare("]"))
			{
				delete Expression;
				Tok = mptr_Lex->GetCurrentToken();
				string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM("]", Tok->getLex().c_str());
				mptr_Lex->m_refErrrorsMod->AddSynError(Tok->getLineNum(), ErrorDesc, "");
				return false;
			}

			delete Expression;
		}


		return false;
	}

}