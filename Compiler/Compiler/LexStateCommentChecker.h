#pragma once
#include "ILexerState.h"
#include <vector>
/*!
\brief Makes sure that comment are closed properly
*/
class LexStateCommentChecker :public ILexerState
{
public:
	LexStateCommentChecker();
	~LexStateCommentChecker();

	bool StateAction(const char * code, uint32_t &Index,
		uint32_t &LineNumber, std::vector<Token> &Tokens,
		std::map<std::string, std::string> *m_Keywords) override;

	void ChangeState(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords, int SelectedState) override;
};

