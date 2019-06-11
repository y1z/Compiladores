#pragma once
#include "ILexerState.h"

class LexStateFinder :
	public ILexerState
{
public:
	LexStateFinder();
	~LexStateFinder();

	bool isKeepGoing = true;

	bool StateAction(const char * code, uint32_t &Index, 
		uint32_t &LineNumber, std::vector<Token> &Tokens, 
		std::map<std::string, std::string> *Keywords) override;

	void ChangeState(const char * code, uint32_t &Index, 
		uint32_t &LineNumber, std::vector<Token> &Tokens, 
		std::map<std::string, std::string> *Keywords, int SelectedState) override;

	bool ChangeStateKeyword(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords);
	bool ChangeStateID(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords);
	bool ChangeStateInvalidChar(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords);
};

