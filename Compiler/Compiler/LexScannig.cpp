#include "stdafx.h"
#include "LexStateCommentChecker.h"
#include "LexScannig.h"

LexScannig::LexScannig()
{}

LexScannig::~LexScannig()
{}

bool LexScannig::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* m_Keywords)
{
	static constexpr const char *Expeted = "/*";

	while (code[Index] != '\0')
	{
		if (code[Index] == '/')
		{
			ILexerState *lexCommit = new LexStateCommentChecker();
			lexCommit->StateAction(code, Index, LineNumber, Tokens, m_Keywords);
			delete lexCommit;
		}

		Index++;
	}
	return false;
}

void LexScannig::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{}

