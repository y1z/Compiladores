#pragma once
#include "ILexerState.h"
#include <vector>
/*!
\brief Makes sure that comment are closed properly
*/


class LexStateCommentChecker :
	public ILexerState
{
public:
	LexStateCommentChecker();
	~LexStateCommentChecker();
	bool StateAcction(const char *code, uint32_t &Index, std::vector<Token> &Tokens) override;

};

