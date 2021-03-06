#include "stdafx.h"
#include "Utility.h"
#include "LexStateCommentChecker.h"
#include "LexIndentifyOperator.h"
#include "LexStringChecker.h"
#include "LexStateFinder.h"
#include "LexSeparators.h"
#include "LexIdentifiyKeyword.h"
#include "LexStateNumber.h"
#include "LexInvalidChar.h"
#include "LexIdentifyIID.h"


LexStateFinder::LexStateFinder()
{}

LexStateFinder::~LexStateFinder()
{}

bool LexStateFinder::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	/*
	 0 = Find-out if LexCommentChecker Or the division operator
	 1 = LexStateLeterialChecker
	 2 = LexIndentifyOperator
	 3 = Separators
	 4 = check for float
	*/
	static std::map<char, int> StateIdentifiers = { {'/',0}, {'\"',1} ,
	{'<',2},{'>',2},{'=',2},{'!',2} ,{'+',2},{'-',2},{'^',2} ,{'*',2} ,{'[',2} ,
	{']',2} ,{'&',2},{'|',2} ,{'(',2} ,{')',2},{'%',2},{'{',2},{'}',2},{'!',2},{';',3 },{',',3},{':',3} ,{'.',4} };

	if (!m_refErrrorsMod->IsMaxErrorReached() && isKeepGoing == true)
	{

		while (code[Index] != ' ' && code[Index] != '\0')
		{/*This is to skip the chars '\r\n' */
			if (code[Index] == '\r' || code[Index] == '\n')
			{ IgnoreNewLineChar(code, Index, LineNumber); }

			auto Iter = StateIdentifiers.find(code[Index]);
			// check if char is valid

			if (Iter != StateIdentifiers.end())
			{
				ChangeState(code, Index, LineNumber, Tokens, Keywords, Iter->second);
				return true;
			}
			else if (IsNumber(code[Index]))
			{
				ChangeState(code, Index, LineNumber, Tokens, Keywords, 4);
			}

			else// checks for Keyword and IDs plus invalid chars 
			{
				if (ChangeStateKeyword(code, Index, LineNumber, Tokens, Keywords)) { return true; }
				else	if (ChangeStateID(code, Index, LineNumber, Tokens, Keywords)) { return true; }
				else if (ChangeStateInvalidChar(code, Index, LineNumber, Tokens, Keywords)) { return true; }
			}
		}
	}

	return false;
}

void LexStateFinder::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{
	if (SelectedState == 0)
	{
		if (code[Index + 1] == '*')
		{
			ILexerState * CommentChecker = new LexStateCommentChecker();
			// for when error occur
			CommentChecker->m_refErrrorsMod = this->m_refErrrorsMod;
			if (!CommentChecker->StateAction(code, Index, LineNumber, Tokens, Keywords));
			{
				isKeepGoing = CheckToStopLexAnalisis(m_refErrrorsMod);
			}

			delete CommentChecker;
			CommentChecker = nullptr;
		}

		else
		{
			ILexerState * OperatorState = new LexIndentifyOperator();
			OperatorState->m_refErrrorsMod = this->m_refErrrorsMod;

			if (OperatorState->StateAction(code, Index, LineNumber, Tokens, Keywords))
			{
				isKeepGoing = CheckToStopLexAnalisis(m_refErrrorsMod);
			}

			delete OperatorState;
			OperatorState = nullptr;
		}

	}//----------
	else if (SelectedState == 1)
	{
		ILexerState * StringChecker = new LexStringChecker();
		StringChecker->m_refErrrorsMod = this->m_refErrrorsMod;
		if (StringChecker->StateAction(code, Index, LineNumber, Tokens, Keywords))
		{
			isKeepGoing = CheckToStopLexAnalisis(m_refErrrorsMod);
		}

		delete StringChecker;
		StringChecker = nullptr;
	}//----------------
	else if (SelectedState == 2)
	{
		ILexerState * OperatorState = new LexIndentifyOperator();
		OperatorState->m_refErrrorsMod = this->m_refErrrorsMod;
		if (OperatorState->StateAction(code, Index, LineNumber, Tokens, Keywords))
		{
			isKeepGoing = CheckToStopLexAnalisis(m_refErrrorsMod);
		}

		delete OperatorState;
		OperatorState = nullptr;
	}//--------------
	else if (SelectedState == 3)
	{
		ILexerState * SeparatorState = new  LexSeparators();
		SeparatorState->m_refErrrorsMod = this->m_refErrrorsMod;

		if (SeparatorState->StateAction(code, Index, LineNumber, Tokens, Keywords))
		{
			isKeepGoing = CheckToStopLexAnalisis(m_refErrrorsMod);
		}


		delete SeparatorState;
		SeparatorState = nullptr;
	}//--------------
	else if (SelectedState == 4)
	{
		ILexerState * NumbersState = new LexStateNumber();
		NumbersState->m_refErrrorsMod = this->m_refErrrorsMod;
		if (NumbersState->StateAction(code, Index, LineNumber, Tokens, Keywords))
		{
			isKeepGoing = CheckToStopLexAnalisis(m_refErrrorsMod);
		}

		delete NumbersState;
		NumbersState = nullptr;
	}
}

bool LexStateFinder::ChangeStateKeyword(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	ILexerState * LexKeyword = new LexIdentifiyKeyword();
	LexKeyword->m_refErrrorsMod = this->m_refErrrorsMod;
	// for reseting the index 
	uint32_t copyIndex = Index;

	bool isKeyword = LexKeyword->StateAction(code, copyIndex, LineNumber, Tokens, Keywords);

	if (isKeyword)
	{
		Index = copyIndex;
	}

	delete LexKeyword;
	LexKeyword = nullptr;
	return isKeyword;
}

bool LexStateFinder::ChangeStateID(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	uint32_t CopyIndex = Index;

	ILexerState * LexIDs = new LexIdentifyIID();

	LexIDs->m_refErrrorsMod = this->m_refErrrorsMod;
	bool isIdValied = LexIDs->StateAction(code, CopyIndex, LineNumber, Tokens, Keywords);

	if (isIdValied)
	{
		//move advance the index 
		Index = CopyIndex;
	}

	delete LexIDs;
	LexIDs = nullptr;
	return isIdValied;
}

bool LexStateFinder::ChangeStateInvalidChar(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	uint32_t CopyIndex = Index;
	ILexerState * ptr_LexInvalidChar = new LexInvalidChar();
	ptr_LexInvalidChar->m_refErrrorsMod = this->m_refErrrorsMod;

	bool isIdValied = ptr_LexInvalidChar->StateAction(code, CopyIndex, LineNumber, Tokens, Keywords);

	if (isIdValied)
	{
		//move advance the index 
		Index = CopyIndex;
	}

	delete ptr_LexInvalidChar;
	ptr_LexInvalidChar = nullptr;
	return isIdValied;
	return false;
}
