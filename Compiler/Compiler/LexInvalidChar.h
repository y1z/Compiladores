#pragma once
#include "ILexerState.h"
/*!
\brief check every single char to make sure there valid and generate an error per each invalid char 
*/

class LexInvalidChar :
	public ILexerState
{
public:
	LexInvalidChar();
	~LexInvalidChar();
	bool StateAction(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords);
	void ChangeState(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords, int SelectedState);

	void CheckForEachInvalidChar(const std::string &buffer,uint32_t LineNumber);
	void AddErroMessage(int Start, int End, uint32_t LineNumber, const std::string & buffer);
public:
	bool isAlreadyChecked = false;
};

