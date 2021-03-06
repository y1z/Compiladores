#pragma once
#include <vcclr.h>
#include <vector>
#include <map>
#include "Usable_Windows.h"
#include "ErrorsModule.h"
#include "Token.h"

namespace Compiler {
	// here are all error that the LexAnalyzer can create.
#define LEX_INVALID_CHAR "\tInvalid Character"
#define STRING_NOT_CLOSED "\tThe string is not closed"
#define COMMENT_NOT_CLOSED "\tThe comment is no closed"
#define INVALID_FLOAT "\tThe float is not valid "
#define INVALID_OP_LOG "\tInvalied use of Logical Operator "
#define INVALID_ID_ENDING "\tInvalid ID. An ID cannot end with an underscore character. "
	/*!
	\brief takes care of the lexical analysis( identifying tokens)
	*/

	class LexAnalyzer
	{
	public:// constructors 
		LexAnalyzer(Compiler::ErrorsModule ^Err);
		~LexAnalyzer();
	public:// functions
			//! where we start to parse the code 
		bool ParseSourceCode(const char *src);
		// used this every time the user is done compiling
		void ClearToken();
		/*! return a pointer to a Token dictated by the variable m_CurrentToken - 1 if possible*/
		bool AdvanceTokenIndex();
		/*! return a pointer to a Token dictated by the variable m_CurrentToken + 1 if possible*/
		bool DecreaseTokenIndex();
		/*! return a pointer to a Token dictated by the variable m_CurrentToken*/
		Token* GetCurrentToken();
		// picks the token from a selected index 
		Token PickToken(std::size_t Index);

		std::size_t GetTokenIndex();
		// gets the total size of the container of tokens 
		std::size_t GetTokenCount();
		// converts the total number of tokens to a string 
		std::string GetTokenCountString();
		//! reruns the container of tokens 
		std::vector<Token>& GetTokenContainer();

		void SetTokenIndex(std::size_t Index);
	public:// variables 
		//! Where all the tokens are kept
		std::vector<Token> m_LexTokens;
		//! has all the keyword are on the left side 
		std::map<std::string, std::string> m_Keywords;
		//! this is a reference to the ErrorsModule
		msclr::gcroot<Compiler::ErrorsModule^> m_refErrrorsMod;
		//! for the get Token function 
		std::size_t m_CurrentToken;
	};

};
