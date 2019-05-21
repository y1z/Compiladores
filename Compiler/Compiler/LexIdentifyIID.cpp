#include "stdafx.h"
#include "Utility.h"
#include <regex>
#include "LexIdentifyIID.h"


LexIdentifyIID::LexIdentifyIID()
{
	/* anything that not a part of the English
	alphabet even things like [,][;][`] etc..*/
	m_InvaliedChars = ("[^A-Za-z]");
}


LexIdentifyIID::~LexIdentifyIID()
{}

bool LexIdentifyIID::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	std::string PossibleID = "";
	while (code[Index] != ' ' && code[Index] != '\0')
	{
		PossibleID += code[Index];
		if (code[Index] == '\0') { break; }
		Index++;
	}

	if (CheckForEnglishLetters(PossibleID))
	{
		Token tok(PossibleID, Compiler::ID, LineNumber);
		Tokens.emplace_back(tok);
	}

	return false;
}

void LexIdentifyIID::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{}

bool LexIdentifyIID::CheckForEnglishLetters(std::string & PossibleIDs)
{
	for (char chr : PossibleIDs)
	{
		if (!IsLetter(chr) && !IsNumber(chr))
		{


		}
	}

	return false;
}

bool LexIdentifyIID::CheckForValidChar(char PossiblyValidChar, std::string &PossibleID, uint32_t Index)
{
	if (PossiblyValidChar == '_' && !(Index >= PossibleID.size() - 1))
	{
		if (IsLetter(PossibleID[Index + 1]) || IsNumber(PossibleID[Index + 1]))
		{
			return true;
		}
	}
	else if (PossiblyValidChar == '_' && Index >= PossibleID.size() - 1)
	{
		return false;
	}

	return false;
}
