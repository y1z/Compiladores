#pragma once
#include "ILexerState.h"
/*! check for both integer and floating-point numbers*/
class LexStateNumber :
	public ILexerState
{
public:
	LexStateNumber();
	~LexStateNumber();//

	bool isFloat = false;

	bool StateAction(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords) override;
	
	void ChangeState(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords, int SelectedState) override;
	//in other word check for this '.' 
	bool CheckForPoint(const char PossiblePoint);
	//! check for things like 3.3.3 or .3 
	bool CheckForValidFloat( std::string &PossibleFloat,uint32_t LineNumber,uint32_t &Index);
	//! check the symbol '-' then added to the buffer 
	void CheckForSign(char PossibleSign,uint32_t &Index);

	std::string m_PossibleMinusSign;
};

