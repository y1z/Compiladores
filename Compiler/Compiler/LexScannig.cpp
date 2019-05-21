#include "stdafx.h"
#include "LexStateCommentChecker.h"
#include "LexStateFinder.h"
#include "LexScannig.h"

LexScannig::LexScannig()
{}

LexScannig::~LexScannig()
{}

bool LexScannig::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	uint32_t CopyIndex = Index;
	uint32_t CopyLine = LineNumber;

	while (code[Index] != '\0')
	{
		// checking for enter presses
		if (code[Index] == '\r')
		{
			LineNumber++;
		}
		else if (code[Index] != ' ')
		{
			ChangeState(code, Index, LineNumber, Tokens, Keywords, 1);
		}
		// just in case 
		if (code[Index] == '\0') { break; }
		Index++;
	}
	return false;
}

void LexScannig::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{
	ILexerState *NewState = new LexStateFinder();
	NewState->m_refErrrorsMod = this->m_refErrrorsMod;

	NewState->StateAction(code, Index, LineNumber, Tokens, Keywords);
	
	for (Token GeneratedTokens : NewState->m_GeneratedTokens)
	{
		this->m_GeneratedTokens.emplace_back(GeneratedTokens);
	}

	delete NewState;
}

