#include "stdafx.h"
#include "LexStateCommentChecker.h"
#include "LexStateFinder.h"
#include "LexScannig.h"
#include "Utility.h"

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
		if (code[Index] == '\r' || code[Index] == '\n')
		{
			IgnoreNewLineChar(code, Index, LineNumber);
		}
		else if (code[Index] != ' ')
		{
			ChangeState(code, Index, LineNumber, Tokens, Keywords, 1);
		}
		// just in case 
		if (code[Index] == '\0') { break; }

		if (code[Index] == ' ' || code[Index] == '\t')
		{
			Index++;
		}

	}
	return true;
}



void LexScannig::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{
	ILexerState *NewState = new LexStateFinder();
	NewState->m_refErrrorsMod = this->m_refErrrorsMod;
	// give it's tokens directly to LexAnalyzer 
	NewState->StateAction(code, Index, LineNumber, Tokens, Keywords);

	delete NewState;
}

