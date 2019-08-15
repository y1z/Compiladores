#include "stdafx.h"
#include "ErrorFunctions.h"
#include "Utility.h"
#include "GlobolNames.h"
#include "SynStateParam.h"

Compiler::SynStateParam::SynStateParam(LexAnalyzer * ptr_Lex, SyntaxAnalysis * ptr_Syn, ISynState * ptr_PrevState, SymbolsTable * ptr_Symblos, SemanticAnalysis * ptr_Semantic)
	:ISynState(ptr_Lex, ptr_Syn, ptr_PrevState, ptr_Symblos, ptr_Semantic)
{
	mptr_VarState = new SynStateVar(ptr_Lex, ptr_Syn, this, ptr_Symblos, ptr_Semantic);
	m_StateName = " State Param ";
	m_CategorySym = SymbolCategory::param;
}

Compiler::SynStateParam::SynStateParam(LexAnalyzer * ptr_Lex, SyntaxAnalysis * ptr_Syn, ISynState * ptr_PrevState, SymbolsTable * ptr_Symblos, SemanticAnalysis * ptr_Semantic, string functionName)
	:ISynState(ptr_Lex, ptr_Syn, ptr_PrevState, ptr_Symblos, ptr_Semantic), m_FuntionName(functionName)
{
	mptr_VarState = new SynStateVar(ptr_Lex, ptr_Syn, this, ptr_Symblos, ptr_Semantic, m_FuntionName);
	m_StateName = " State Param ";
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
	if (CompareTokenTypes(Tok, GNames::t_ID))
	{
		// making sure i don't get a param twice
		bool alreadyGot = false;
		LocalNode Temp;

		Temp.SetSymbol(Tok->getLex().c_str());

		IsValid = mptr_Lex->AdvanceTokenIndex();
		Tok = mptr_Lex->GetCurrentToken();

		Temp.SetLineNum(Tok->getLineNum());

		if (!Tok->getLex().compare("["))
		{
			Temp.SetDimension(mptr_VarState->FindDimension());
			Tok = mptr_Lex->GetCurrentToken();
			alreadyGot = true;
			m_Nodes.emplace_back(Temp);
		}
		//recursion
		if (!Tok->getLex().compare(","))
		{
			if (alreadyGot == false)
			{
				m_Nodes.emplace_back(Temp);
			}
			return this->CheckSyntax();
		}

		if (!Tok->getLex().compare(":"))
		{
			m_Nodes.emplace_back(Temp);
			IsValid = mptr_VarState->CheckForValidType();

			if (IsValid)
			{
				m_Type = mptr_Lex->GetCurrentToken()->getLex();
			}
			return IsValid;
		}
		else
		{
			string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(":", Tok->getLex().c_str());
			mptr_Lex->m_refErrrorsMod->AddSynError(Tok->getLineNum(), ErrorDesc, "");
			return false;
		}
	}
	// making sure they close the parenthesis
	if (!Tok->getLex().compare(")"))
	{
		mptr_Lex->DecreaseTokenIndex();
		return false;
	}
	return MoveAndAssignTokenIndex(mptr_Lex, Tok);

}

std::vector<Compiler::LocalNode> Compiler::SynStateParam::GetNodes()
{
	auto Result = m_Nodes;

	return Result;
}
