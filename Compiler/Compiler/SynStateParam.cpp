#include "stdafx.h"
#include "ErrorFunctions.h"
#include "GlobolNames.h"
#include "SynStateParam.h"

Compiler::SynStateParam::SynStateParam(LexAnalyzer * ptr_Lex, SyntaxAnalysis * ptr_Syn, ISynState * ptr_PrevState, SymbolsTable * ptr_Symblos, SemanticAnalysis * ptr_Semantic)
	:ISynState(ptr_Lex, ptr_Syn, ptr_PrevState, ptr_Symblos, ptr_Semantic)
{
	mptr_VarState = new SynStateVar(ptr_Lex, ptr_Syn, this, ptr_Symblos, ptr_Semantic);
	m_StateName = "SynState : Param ";
	m_CategorySym = SymbolCategory::param;
}

Compiler::SynStateParam::~SynStateParam()
{
	delete mptr_VarState;
}

//! Already found the "(" char 
bool Compiler::SynStateParam::CheckSyntax()
{
	ReadOnlyToken Tok = nullptr;

	MoveAndAssignTokenIndex(mptr_Lex, Tok);

	// get ID 
	if (CompareTokenTypes(Tok, g_Names::t_ID))
	{
		std::pair<std::string, int> NameAndDim;
		NameAndDim.first = Tok->getLex();

		IsValid = mptr_Lex->AdvanceTokenIndex();
		Tok = mptr_Lex->GetCurrentToken();

		if (!Tok->getLex().compare("["))
		{
			NameAndDim.second = mptr_VarState->FindDimension();
			Tok = mptr_Lex->GetCurrentToken();
		}
		//recursion
		if (!Tok->getLex().compare(","))
		{
			NameAndDim.second = 0;
			return this->CheckSyntax();
		}

		if (!Tok->getLex().compare(":"))
		{
			IsValid = mptr_VarState->CheckForValidType();
			return IsValid;
		}
		else
		{
			string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(":", Tok->getLex().c_str());
			mptr_Lex->m_refErrrorsMod->AddSynError(Tok->getLineNum(), ErrorDesc, "");
			return false;
		}
	}
	MoveAndAssignTokenIndex(mptr_Lex, Tok);
	// making sure they close the parenthesis
	return false;
}