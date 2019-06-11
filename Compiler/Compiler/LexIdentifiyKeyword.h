#pragma once
#include "ILexerState.h"
class LexIdentifiyKeyword :
	public ILexerState
{
public:
	LexIdentifiyKeyword();
	~LexIdentifiyKeyword();
public: // functions 
	bool StateAction(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords)override;
	// basically check for 'true' and 'false'
	bool CheckKeywordExecptions(std::string &Keyword, uint32_t LineNumber);

	void ChangeState(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords, int SelectedState)override;
};

