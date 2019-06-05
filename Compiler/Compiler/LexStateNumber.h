#pragma once
#include "ILexerState.h"
/*! check for both integer and floating-point numbers*/
class LexStateNumber :
	public ILexerState
{
public:
	LexStateNumber();
	~LexStateNumber();

	bool isFloat = false;

	bool StateAction(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords) override;
	
	void ChangeState(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords, int SelectedState) override;
	//in other word check for this '.' 
	bool CheckForPoint(const char PossiblePoint);

	bool CheckForValidFloat( std::string &PossibleFloat,uint32_t LineNumber);
};

