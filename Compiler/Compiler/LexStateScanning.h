#pragma once
#include "ILexerState.h"
class LexStateScanning :
	public ILexerState
{
public:
	LexStateScanning();
	~LexStateScanning();
	bool StateAcction(const char *code, uint32_t &Index, std::vector<Token> &Tokens);
};

