#pragma once
#include <vcclr.h>
#include <cinttypes>
#include <vector>
#include <map>
#include "LexAnalyzer.h"
#include "Token.h"
#include "ErrorsModule.h"

class ILexerState
{
public:
	ILexerState();
	virtual ~ILexerState();
	/*! checks if the operation was successful 
	\param code [in] this is a pointer to the source code that being parsed.
	\param Index [in][out] this is so every individual state can know where to start in the source code.
	\param Tokens [out] this is where all the token for the LexAnalyzer are sorted.
	\param Keywords [int] this will be used the identify keywords */
	virtual bool StateAction(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords) = 0;
	/*! used to change State which so each one can do it action*/
	virtual void ChangeState(const char * code, uint32_t &Index, uint32_t &LineNumber, std::vector<Token> &Tokens, std::map<std::string, std::string> *Keywords,int SelectedState) = 0;
	//! For sending error messages to the ErrorsModule class  
	msclr::gcroot<Compiler::ErrorsModule ^> m_refErrrorsMod;
	//! the token generated be this class
	std::vector<Token> m_GeneratedTokens;
	//! For when errors Happen
	std::vector <std::pair<std::string,std::string>> m_ErrorContainer;
};

