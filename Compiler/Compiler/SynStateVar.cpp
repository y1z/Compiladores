#include "stdafx.h"
#include "SynStateVar.h"
#include "Utility.h"
#include "GlobolNames.h"
#include "ErrorFunctions.h"
#include <tuple>

Compiler::SynStateVar::SynStateVar(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic)
	:ISynState(ptr_Lex, ptr_Syn, ptr_PrevState, ptr_Symblos,ptr_Semantic)
{
	m_StateName = "State Var";
}

Compiler::SynStateVar::~SynStateVar()
{}
//! entering here we already seen the keyword 'var' 
bool Compiler::SynStateVar::CheckSyntax()
{
	mptr_Lex->AdvanceTokenIndex();
	mptr_Token = mptr_Lex->GetCurrentToken();

	string TokenTypeStr(TranslateToken(mptr_Token->getType()));
	//this is where I will keep the name and dim of the vars 
	auto NameAndDim = std::pair<std::string, int>();
	// find out if we get an ID 
	if (!TokenTypeStr.compare(g_Names::t_ID))
	{
		NameAndDim.first = mptr_Token->getLex();

		mptr_Lex->AdvanceTokenIndex();

		mptr_Token = mptr_Lex->GetCurrentToken();
		//for when the var ID is an array
		if (!mptr_Token->getLex().compare("["))
		{
			uint32_t Dim = FindDimension();
			NameAndDim.second = Dim;
			m_VarsList.emplace_back(NameAndDim);
		}
		else
		{
			NameAndDim.second = 0;
			m_VarsList.emplace_back(NameAndDim);
		}
	}
	else// received a char that i was not expecting 
	{
		string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(g_Names::t_ID, TokenTypeStr.c_str());
		mptr_Lex->m_refErrrorsMod->AddSynError(mptr_Token->getLineNum(), ErrorDesc, "");
		isValid = false;
	}
	//mptr_Lex->AdvanceTokenIndex();
	mptr_Token = mptr_Lex->GetCurrentToken();
	// --- check if the line was ended properly aka with a ';'
	CheckRecursionOrLineEnding();

	// will be used for paramas and other things 
	if (isValid)
	{

		if (m_CategorySym != SymbolCategory::global_var)
		{
			mptr_Lex->DecreaseTokenIndex();
			m_VarType = mptr_Lex->GetCurrentToken()->getLex();
			mptr_Lex->AdvanceTokenIndex();

			mptr_SymbolsTable->AddSymbol(NameAndDim.first, NameAndDim.second, m_CategorySym, this->m_FunctionName, m_VarType);
		}
		else
		{
			mptr_Lex->DecreaseTokenIndex();
			m_VarType = mptr_Lex->GetCurrentToken()->getLex();
			mptr_Lex->AdvanceTokenIndex();

			mptr_SymbolsTable->AddSymbol(NameAndDim.first, NameAndDim.second, m_CategorySym, g_Names::GlobalScope, m_VarType);
		}
	}


	return isValid;
}

uint32_t Compiler::SynStateVar::FindDimension()
{
	/// we already know that we found an id
	mptr_Lex->AdvanceTokenIndex();
	// representation of the expected char's from this stage in the state 
	string ExpectedSequnce = { "n]" };
	// where we are 
	uint8_t SequencePos = 0;
	// the return value
	uint32_t Result = 0;

	while (SequencePos < ExpectedSequnce.size())
	{
		this->mptr_Token = mptr_Lex->GetCurrentToken();
		// find out what the number is 
		if (ExpectedSequnce[SequencePos] == 'n')
		{
			if (!mptr_Lex->GetCurrentToken()->getLex().compare("-"))
			{
				mptr_Lex->AdvanceTokenIndex();
				Result = std::stoi(mptr_Token->getLex());
				Result = Result * -1;
				mptr_Lex->AdvanceTokenIndex();
				SequencePos++;
			}
			else
			{
				Result = std::stoi(mptr_Token->getLex());
				mptr_Lex->AdvanceTokenIndex();
				SequencePos++;
			}

		}
		else if (ExpectedSequnce[SequencePos] != 'n')// check if the other parts are correct 
		{
			if (!mptr_Token->getLex().compare(&ExpectedSequnce[SequencePos]))
			{
				SequencePos++;
				mptr_Lex->AdvanceTokenIndex();
			}
			else
			{
				ErrorFuncs::SYN_UNEXPECTED_SYM(&ExpectedSequnce[SequencePos], mptr_Token->getLex().c_str());
				break;
			}
		}

	}


	return Result;
}

bool Compiler::SynStateVar::CheckForValidType()
{
	mptr_Lex->AdvanceTokenIndex();
	mptr_Token = mptr_Lex->GetCurrentToken();

	for (string ValidTypes : g_Names::AllVarAfter)
	{
		if (!mptr_Token->getLex().compare(ValidTypes))
		{
			return true;
		}
	}
	string ErrorDecs = ErrorFuncs::SYN_UNEXPECTED_SYM("'<int>|<float>|<string>|<bool>'", mptr_Token->getLex().c_str());
	mptr_Lex->m_refErrrorsMod->AddSynError(mptr_Token->getLineNum(), ErrorDecs, "");

	return false;
}

bool Compiler::SynStateVar::CheckRecursionOrLineEnding()
{
	// recursion
	if (!mptr_Token->getLex().compare(","))
	{
		this->CheckSyntax();
	}
	// making sure that the ending is valid 
	else if (!mptr_Token->getLex().compare(":"))
	{
		isValid = this->CheckForValidType();
		if (isValid)
		{
			mptr_Lex->AdvanceTokenIndex();
			mptr_Token = mptr_Lex->GetCurrentToken();
			// check for when the ';' char is not there
			if (mptr_Token->getLex().compare(g_Names::d_LineEnd))
			{
				string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(g_Names::d_LineEnd, mptr_Token->getLex().c_str());
				this->mptr_Lex->m_refErrrorsMod->AddSynError(mptr_Token->getLineNum(), ErrorDesc, "");
				isValid = false;
			}
		}
	}
	return isValid;
}
