#include "stdafx.h"
#include "SynStatePrint.h"
#include "SynStateExpLog.h"
#include "Utility.h"
#include "ErrorFunctions.h"

Compiler::SynStatePrint::SynStatePrint(LexAnalyzer * Lex, SyntaxAnalysis * Syn, ISynState * PrevState, SymbolsTable * Symblos, SemanticAnalysis * Semantic, string FunctionName)
	:ISynState(Lex, Syn, PrevState, Symblos, Semantic), m_FunctionName(FunctionName)
{
	this->m_StateName = " Print State ";
}

Compiler::SynStatePrint::~SynStatePrint()
{}
// already found the world Print 
bool Compiler::SynStatePrint::CheckSyntax()
{
	string ExpectedSequence = { "(e);" };
	ReadOnlyToken tok = mptr_Lex->GetCurrentToken();

	for (char Indacator : ExpectedSequence)
	{
		if (Indacator == 'e')
		{
			ISynState * Expression = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
			Expression->CheckSyntax();
			tok = mptr_Lex->GetCurrentToken();//
			delete Expression;
		}
		else
		{
			if (tok->getLex().compare(&Indacator))
			{
				const char *Temp = &Indacator;
				string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(Temp, tok->getLex().c_str());
				mptr_Lex->m_refErrrorsMod->AddSynError(tok->getLineNum(), ErrorDesc, "");
			}
			MoveAndAssignTokenIndex(mptr_Lex, tok);
		}
	}



	return true;
}
