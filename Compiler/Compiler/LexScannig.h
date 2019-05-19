#pragma once
#include "ILexerState.h"
class LexScannig :
	public ILexerState
{
public:
	LexScannig();
	~LexScannig();

	bool StateAction(const char * code, uint32_t &Index,
		uint32_t &LineNumber, std::vector<Token> &Tokens,
		std::map<std::string, std::string> *m_Keywords) override;

	void ChangeState(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords, int SelectedState) override;
};

