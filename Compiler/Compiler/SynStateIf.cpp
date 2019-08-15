#include "stdafx.h"
#include "Utility.h"
#include "ErrorFunctions.h"
#include "SynStateIf.h"
#include "SynStateExpLog.h"
#include "SynStateElse.h"
#include "SynStateSubFunctionBlock.h"
namespace Compiler {

	SynStateIf::SynStateIf(LexAnalyzer * Lex, SyntaxAnalysis * Syn, ISynState * PrevState, SymbolsTable * Symblos, SemanticAnalysis * Semantic, string & functionName)
		:ISynState(Lex, Syn, PrevState, Symblos, Semantic), m_FunctionName(functionName)
	{
		m_StateName = "IF State";
	}

	SynStateIf::~SynStateIf()
	{}
	// Already found the 'if' keyword 
	bool SynStateIf::CheckSyntax()
	{
		ISynState * ExpLog = new SynStateExpLog(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName, "{");

		ExpLog->CheckSyntax();

		ReadOnlyToken token = mptr_Lex->GetCurrentToken();
		delete ExpLog;

		if (!token->getLex().compare("{"))
		{
			ISynState *SubFuncBlock = new SynStateSubFunctionBlock(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
			SubFuncBlock->CheckSyntax();
			delete SubFuncBlock;
			// check for an else block 
			token = mptr_Lex->GetCurrentToken();
			if(!token->getLex().compare(GNames::k_Else))
			{
				MoveAndAssignTokenIndex(mptr_Lex, token);
				ISynState *SubFuncBlock = new SynStateElse(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);
				bool Result = SubFuncBlock->CheckSyntax();
				delete SubFuncBlock;
				return Result;
			}

			return true;
		}
		else
		{
			string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM("{", token->getLex().c_str());
			mptr_Lex->m_refErrrorsMod->AddSynError(token->getLineNum(), ErrorDesc, "");
			return true;
		}

		return false;
	}
}