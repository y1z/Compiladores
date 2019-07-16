#include "stdafx.h"
#include "SynStateElse.h"
#include "SynStateSubFunctionBlock.h"
#include "ErrorFunctions.h"
namespace Compiler {

	SynStateElse::SynStateElse(LexAnalyzer * Lex, SyntaxAnalysis * Syn, ISynState * PrevState, SymbolsTable * Symblos, SemanticAnalysis * Semantic, const string & FunctionName)
		:ISynState(Lex, Syn, PrevState, Symblos, Semantic), m_FunctionName(FunctionName)
	{
		m_StateName = "Else State";
	}

	SynStateElse::~SynStateElse()
	{}
	// Already found the else keyword 
	bool SynStateElse::CheckSyntax()
	{
		ReadOnlyToken tok = mptr_Lex->GetCurrentToken();
		if (!tok->getLex().compare("{"))
		{
			ISynState * FuncBlock = new SynStateSubFunctionBlock(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, m_FunctionName);

			FuncBlock->CheckSyntax();
			delete FuncBlock;
			return true;
		}else
		{
			string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM("{", tok->getLex().c_str());
			mptr_Lex->m_refErrrorsMod->AddSynError(tok->getLineNum(), tok->getLex(), "");
			return false;
		}

		return false;
	}


}