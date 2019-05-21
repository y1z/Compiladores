#pragma once
#include "ILexerState.h"
class LexSeparators :
	public ILexerState
{
public:
	LexSeparators();
	~LexSeparators();

	bool StateAction(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords);

	void ChangeState(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords, int SelectedState);

	bool IsSeparators(char PosibleSeparator);

	std::vector<char> Sparators = { ',',';',':' };
};

