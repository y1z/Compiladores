#pragma once
#include "ILexerState.h"
class LexIdentifyIID :
	public ILexerState
{
public:
	LexIdentifyIID();
	~LexIdentifyIID();

	bool isValidID = false;

	bool StateAction(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords);
	void ChangeState(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords, int SelectedState);

	bool CheckForValidSequence(std::string &PossibleIDs, uint32_t &Index);
	// check if the non English char is still valid to use
	bool CheckForValidChar(char PossiblyValidChar,std::string &PossibleID,uint32_t Index);
};

