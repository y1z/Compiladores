#pragma once
#include "ILexerState.h"
/*!
\file
\brief This class find and classifies all operator,logical,relational,arithmetic etc...*/

class LexIndentifyOperator :
	public ILexerState
{
public:
	LexIndentifyOperator();
	~LexIndentifyOperator();

	bool StateAction(const char * code, uint32_t &Index,
		uint32_t &LineNumber, std::vector<Token> &Tokens,
		std::map<std::string, std::string> *Keywords) override;

	void ChangeState(const char * code, uint32_t &Index,
		uint32_t &LineNumber, std::vector<Token> &Tokens,
		std::map<std::string, std::string> *Keywords, int SelectedState) override;
	/*! Here goes all operator who's consistence is of one char and find where it belongs 
	\param [in] Op The operator 
	\param [in] LineNum is for the token .
	*/
	bool FiguerOutOperator(char Op, uint32_t LineNum,std::vector<Token> &Tokens);
	/*! used to figure out if a char is an operator */
	bool isOperator(char PossibleOperator);

	/*! checks if the operator has an equal sign next to it returns with or without the equals-sign
	\param [in] the code in question
	\param [in][out] the place we are in the code */
	std::string ReciveRelationalOperator(const char *code, uint32_t& Index);
	/*! checks if Operator is valid
	\param [in] the code
	\param [in][out] to know where we are
	\param [out] the resulting operator*/
	bool  CheckOperatorValid(const char *code, uint32_t& Index, std::string &PosibleOperator);
public: // variables 

	static std::map<char, int> Operators;
};
