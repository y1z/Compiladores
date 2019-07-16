#include "stdafx.h"
#include "ErrorFunctions.h"
#include "SynStateWhile.h"
#include "SynStateExpLog.h"

namespace Compiler {

	SynStateWhile::SynStateWhile(LexAnalyzer * Lex, SyntaxAnalysis * Syn, ISynState * PrevState, SymbolsTable * Symblos, SemanticAnalysis * Semantic, const string & FunctionName)
		:ISynState(Lex, Syn, PrevState, Symblos, Semantic), m_FunctionName(FunctionName)
	{
		m_StateName = " While State ";
	}

	SynStateWhile::~SynStateWhile()
	{}
	// already found the while keyword 
	bool SynStateWhile::CheckSyntax()
	{
		string ExpectedSequence{ "(e)" };
		std::int8_t SequencePos = 0;

		for (const char ChrOrState : ExpectedSequence)
		{
			ReadOnlyToken Tok = mptr_Lex->GetCurrentToken();
			if (ExpectedSequence[SequencePos] == 'e')
			{// advancing
				SequencePos++;

				ISynState *ExpLog = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);

				ExpLog->CheckSyntax();
				mptr_Lex->DecreaseTokenIndex();
				delete ExpLog;
			}
			else
			{// advancing
				SequencePos++;
				string Temp{ ChrOrState };
				if (!Tok->getLex().compare(Temp))
				{
					continue;
				}
				else
				{
					string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(Temp.c_str(), Tok->getLex().c_str());
					mptr_Lex->m_refErrrorsMod->AddSynError(Tok->getLineNum(), ErrorDesc, "");
				}
			}

		}

		return false;
	}

}