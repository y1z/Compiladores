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
	/*! find all char that could be invalid */
	void CheckForEachInvalidChar(const std::string &buffer, uint32_t LineNumber);
	/*! add error I found a invalid char */
	void AddErroMessage(int Start, int End, uint32_t LineNumber, const std::string & buffer);
	/*! divide the valid char from the invalid one and check what they are */
	std::vector<std::string> DivideBuffer(const std::string &Buffer);
	/*! Get the difference(in index positions) between two values*/
	std::size_t GetDelta(std::size_t PrevIndex, std::size_t NextIndex);
public:
	std::vector<int> m_InvalidCharPos;
	bool isAlreadyChecked = false;
	//! this is guard from  recursion 
	inline static bool isRecursive = false;
};
