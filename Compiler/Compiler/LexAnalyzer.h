#pragma once
#include <vcclr.h>
#include <vector>
#include <map>
#include "Usable_Windows.h"
#include "ILexerState.h"
#include "ErrorsModule.h"
#include "Token.h"

namespace Compiler {
#define LEX_INVALID_CHAR "Invalid Character"
#define STRING_NOT_CLOSED "The string is not closed"
#define COMMENT_NOT_CLOSED "The comment is no closed"
#define INVALID_FLOAT "The float is not valid "
#define INVALID_OP_LOG "Invalied use of Logical Operator "
	/*!
	\brief takes care of the lexical analysis( identifying tokens)*/
	public class LexAnalyzer
	{
	public:
		LexAnalyzer(ErrorsModule ^Err);
		~LexAnalyzer();
	public:// functions
		bool ParseSourceCode(const char *src);
		// used this every time the user is done compiling
		void clearToken();
		void getTokens(std::vector<Token> TokensVec);
		Token getNextToken();
		Token getPrevToken();
		Token PickToken(std::size_t Index);
		Token peckToken();
	public: // variables
		//ILexerState *mptr_CurrentState = nullptr;
		std::vector<Token> m_tokens;
		//! has all the keyword are on the left side 
		std::map<std::string, std::string> m_Keywords;
		msclr::gcroot<ErrorsModule ^> m_refErrrorsMod;
		//! for the get Token function 
		std::size_t m_CurrentToken;
	};
}


