#pragma once
#include "ILexerState.h"
#include <regex>
class LexIdentifyIID :
	public ILexerState
{
public:
	LexIdentifyIID();
	~LexIdentifyIID();

	std::regex m_InvaliedChars;

	bool StateAction(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords);
	void ChangeState(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords, int SelectedState);

	bool CheckForEnglishLetters(std::string &PossibleIDs);
	// check if the non English char is still valid to use
	bool CheckForValidChar(char PossiblyValidChar,std::string &PossibleID,uint32_t Index);
};

