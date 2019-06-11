#pragma once
#include "ILexerState.h"
#include <map>
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
	/*! find all char that are invalid (basically, there not id's or keywords) */
	void CheckForEachInvalidChar(const std::string &buffer, uint32_t LineNumber);
	/*! add error I found a invalid char */
	void AddErroMessage(std::string &ErrorLine, uint32_t LineNumber);
	/*! starts a LexFinder state to determinate if there ID's,keywords, etc...*/
	std::vector<std::string> CheckAllValidChars(const std::vector<bool> &ValidCharIndexes,const std::string &buffer);
	/*! Create all the string that will be used in the error message */
	std::vector<std::string> GenerateErrorStrings(const std::string &Buffer);
	/*! Get the difference(in index positions) between two values*/
	std::size_t GetDelta(std::size_t PrevIndex, std::size_t NextIndex);
	/*! used to distinguish invalid char from invalid ones , using a group of bools.*/
	std::vector<bool> FindValidChars(std::size_t bufferSize);
public:
	// keeps track of the char that are invalid and where they are in the string 
	std::vector<std::pair<int,char>> m_InvalidCharAndPositions;

	bool isAlreadyChecked = false;
	//! this is guard from  recursion 
	inline static bool isRecursive = false;
};
