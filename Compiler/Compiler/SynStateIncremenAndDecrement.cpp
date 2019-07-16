#include "stdafx.h"
#include "SynStateIncremenAndDecrement.h"
#include "ErrorFunctions.h"
#include "GlobolNames.h"

namespace Compiler {

	SynStateIncremenAndDecrement::SynStateIncremenAndDecrement(
		LexAnalyzer *Lex, SyntaxAnalysis *Syn, 
		ISynState *PrevState, SymbolsTable *Symblos, 
		SemanticAnalysis *Semantic, const string &FunctionName)
		:ISynState(Lex, Syn, PrevState, Symblos, Semantic),m_FunctionName(FunctionName)
	{
		m_StateName = " Increment or Decrement state ";
	}


	SynStateIncremenAndDecrement::~SynStateIncremenAndDecrement()
	{}
	// already found inc or dec 
	bool SynStateIncremenAndDecrement::CheckSyntax()
	{
		ReadOnlyToken token = mptr_Lex->GetCurrentToken();
		if(CompareTokenTypes(token,GNames::t_Int))
		{
			return true;
		}
		else
		{
			string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM("<INT_NUMBER>", token->getLex().c_str());
			mptr_Lex->m_refErrrorsMod->AddSynError(token->getLineNum(), ErrorDesc, "");
			return false;
		}

		return false;
	}

}