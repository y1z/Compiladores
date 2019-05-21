#include "stdafx.h"
#include "Utility.h"
#include "LexStateCommentChecker.h"
#include "LexIndentifyOperator.h"
#include "LexStringChecker.h"
#include "LexStateFinder.h"
#include "LexSeparators.h"
#include "LexIdentifiyKeyword.h"
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
	*/
	static std::map<char, int> StateIdentifiers = { {'/',0}, {'\"',1} ,
	{'<',2},{'>',2},{'=',2},{'!',2} ,{'+',2},{'-',2},{'^',2} ,{'*',2} ,{'[',2} ,
	{']',2} ,{'&',2},{'|',2} ,{'{',2},{'}',2},{'!',2},{';',3 },{',',3},{':',3} };

	while (code[Index] != ' ' || code[Index] != '\0')
	{
		if (code[Index] == '\r') { LineNumber++; }
		auto Iter = StateIdentifiers.find(code[Index]);
		// check if char is valid

		if (Iter != StateIdentifiers.end())
		{
			ChangeState(code, Index, LineNumber, Tokens, Keywords, Iter->second);
			return true;
		}
		else// checks for Keyword and IDs 
		{
			if (ChangeStateKeyword(code,Index,LineNumber,Tokens,Keywords)) { return true; }
			else	if (ChangeStateID(code, Index, LineNumber, Tokens, Keywords)) { return true; }
		}
		// for safety
		if (code[Index] == 0)
		{ break; }
		Index++;
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
			CommentChecker->StateAction(code, Index, LineNumber, Tokens, Keywords);

			for (auto Tokens : CommentChecker->m_GeneratedTokens)
			{
				this->m_GeneratedTokens.emplace_back(Tokens);
			}

			delete CommentChecker;
		}

		else
		{
			ILexerState * OperatorState = new LexIndentifyOperator();
			OperatorState->m_refErrrorsMod = this->m_refErrrorsMod;
			OperatorState->StateAction(code, Index, LineNumber, Tokens, Keywords);

			for (Token Generated : OperatorState->m_GeneratedTokens)
			{
				this->m_GeneratedTokens.emplace_back(Generated);
			}

			delete OperatorState;
		}

	}//----------
	else if (SelectedState == 1)
	{
		ILexerState * StringChecker = new LexStringChecker();
		StringChecker->m_refErrrorsMod = this->m_refErrrorsMod;
		StringChecker->StateAction(code, Index, LineNumber, Tokens, Keywords);

		for (Token OtherTokens : StringChecker->m_GeneratedTokens)
		{
			this->m_GeneratedTokens.emplace_back(OtherTokens);
		}

		delete StringChecker;
	}//----------------
	else if (SelectedState == 2)
	{
		ILexerState * OperatorState = new LexIndentifyOperator();
		OperatorState->m_refErrrorsMod = this->m_refErrrorsMod;
		OperatorState->StateAction(code, Index, LineNumber, Tokens, Keywords);

		for (Token Generated : OperatorState->m_GeneratedTokens)
		{
			this->m_GeneratedTokens.emplace_back(Generated);
		}

		delete OperatorState;
	}
	else if (SelectedState == 3)
	{
		ILexerState * SeparatorState = new  LexSeparators();
		SeparatorState->m_refErrrorsMod = this->m_refErrrorsMod;
		SeparatorState->StateAction(code, Index, LineNumber, Tokens, Keywords);
		for (Token Generated : SeparatorState->m_GeneratedTokens)
		{
			this->m_GeneratedTokens.emplace_back(Generated);
		}
		delete SeparatorState;
	}

}

bool LexStateFinder::ChangeStateKeyword(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	ILexerState * LexKeyword = new LexIdentifiyKeyword();
	LexKeyword->m_refErrrorsMod = this->m_refErrrorsMod;
	bool isKeyword = LexKeyword->StateAction(code, Index, LineNumber, Tokens, Keywords);
	TrasferToken(this, LexKeyword);

	delete LexKeyword;
	return isKeyword;
}

bool LexStateFinder::ChangeStateID(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	ILexerState * LexIDs = new LexIdentifyIID();
	LexIDs->m_refErrrorsMod = this->m_refErrrorsMod;
	bool isIdValied = LexIDs->StateAction(code, Index, LineNumber, Tokens, Keywords);
	TrasferToken(this, LexIDs);

	delete LexIDs;
	return isIdValied;
}
