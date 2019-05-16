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
	/*! C++ Class*/
	public class LexAnalyzer
	{
	public:
		LexAnalyzer(ErrorsModule ^Err);
		~LexAnalyzer();
	public:// functions
		bool ParseSourceCode(const char *src);
		// used this every time the user compliers
		void clearToken();
		void getTokens(std::vector<Token *> * TokensVec);
		Token *getNextToken();
		Token *getPrevToken();
		Token *peckToken();
	public: // variables
		std::vector<Token *> m_tokens;
		std::map<std::string, std::string> m_Keywords;
		msclr::gcroot<ErrorsModule ^> m_reErrrorsMod;
	};
}


