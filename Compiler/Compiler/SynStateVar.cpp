#include "stdafx.h"
#include "SynStateVar.h"
#include "Utility.h"
#include "GlobolNames.h"
#include "ErrorFunctions.h"

Compiler::SynStateVar::SynStateVar(LexAnalyzer * ptr_Lex, SyntaxAnalysis * ptr_Syn, ISynState * ptr_PrevState, SymbolsTable * ptr_Symblos)
	:ISynState(ptr_Lex, ptr_Syn, ptr_PrevState, ptr_Symblos)
{
	m_StateName = "State Var";
}

Compiler::SynStateVar::~SynStateVar()
{}
//! entering here we already seen the keyword 'var' 
bool Compiler::SynStateVar::CheckSyntax()
{
	mptr_Token = mptr_Lex->GetPeekToken();

	bool isValid = true;

	while (isValid)
	{
		const char *ptr_Temp = TranslateToken(mptr_Token->getType());

		if (ptr_Temp == g_Names::t_ID)
		{
			mptr_Lex++;
			mptr_Token = mptr_Lex->GetPeekToken();
			//for when the var ID is an array
			if (!mptr_Token->getLex().compare("["))
			{
				uint32_t Dim = FindDimension();
			}
			else if (IsNumberSequence(mptr_Token->getLex()))
			{
				std::stoi(mptr_Token->getLex());

			}
			else
			{

			}
		}
		else// received a char that i was not expecting 
		{
			string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(g_Names::t_ID, ptr_Temp);
			mptr_Lex->m_refErrrorsMod->AddSynError(mptr_Token->getLineNum(), ErrorDesc, "");
			break;
		}
	}

	return false;
}

uint32_t Compiler::SynStateVar::FindDimension()
{
	/// we already know that we found an id
	mptr_Lex->AdvanceTokenIndex();
	// representation of the expected char's from this stage in the state 
	string ExpectedSequnce = { "n],"};
	// where we are 
	short SequencePos = 0;
	// the return value
	uint32_t Result = 0;

	while (SequencePos < ExpectedSequnce.size())
	{
		this->mptr_Token = mptr_Lex->GetPeekToken();
		// find out what the number is 
		if (ExpectedSequnce[SequencePos] == 'n')
		{
			Result = std::stoi(mptr_Token->getLex());
		}
		else// check if the other parts are correct 
		{
			if (!mptr_Token->getLex().compare(&ExpectedSequnce[SequencePos]))
			{
				SequencePos++;
				mptr_Lex->AdvanceTokenIndex();
			}
			else
			{
				ErrorFuncs::SYN_UNEXPECTED_SYM(&ExpectedSequnce[SequencePos], mptr_Token->getLex().c_str());
			}
		}

	}


	return Result;
}
