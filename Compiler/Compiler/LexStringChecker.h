#pragma once
#include "ILexerState.h"
class LexStringChecker :
	public ILexerState
{
public:
	LexStringChecker();
	~LexStringChecker();
	/*! make sure that string are closed properly*/
	bool StateAction(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords);

	void ChangeState(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords, int SelectedState);
	/*! */
	void ReportError(uint32_t LineNumber, const char * code, uint32_t Index,const char *CustomMessage = nullptr);
};

