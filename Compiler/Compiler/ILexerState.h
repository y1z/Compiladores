#pragma once
#include <vcclr.h>
#include <cinttypes>
#include <vector>
#include "LexAnalyzer.h"
#include "Token.h"
class ILexerState
{
public:
	ILexerState();
	virtual ~ILexerState();
	/*! checks if the operation was successful 
	\param code [in] this is a pointer to the source code that being parsed.
	\param Index [in][out] this is so every individual state can know where to start in the source code.
	\param Tokens [out] this is where all tokens are stored.*/
	virtual bool StateAcction(const char *code, uint32_t &Index,std::vector<Token> &Tokens) = 0;

};

