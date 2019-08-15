#include "stdafx.h"
#include "TestingClass.h"
#include "LexStateCommentChecker.h"
#include "LexStringChecker.h"
#include <memory>

static constexpr int TotalTest = 6;

namespace Compiler {

	TestingClass::TestingClass()
	{
		m_Results = gcnew cli::array<bool^>(TotalTest);
		for (int i = 0; i < TotalTest; ++i)
		{
			m_Results[i] = false;
		}

		mref_Error = gcnew Compiler::ErrorsModule;

	}

	void TestingClass::RunTests()
	{
		Compiler::Token_Type Test = (Compiler::Token_Type)0;
		bool Result0 = true;
		//------------------------------------------------------------------------
		// testing to make sure we don't get the ERROR message 
		for (int i = 0; i < 14; ++i)
		{
			std::string Temp(TranslateToken(Test));
			if (!Temp.compare("ERROR"))
			{
				Result0 = false;
			}
			Test = (Compiler::Token_Type)i;
		}
		// adding the result 
		AddResult(Result0, 0);
		//------------------------------------------------------------------------
		// testing the IsNumber function to make sure it only return true for char that represent numbers 
		bool Result1 = true;
		string Numbers = "1234567890";
		string Letters = "qwertyuiopasdfghjklzxcvbnm";

		for (char StrNum : Numbers)
		{
			if (IsNumber(StrNum) == false) { Result1 = false; }
		}

		for (char StrLetter : Letters)
		{
			if (IsNumber(StrLetter) == true) { Result1 = false; }
		}

		AddResult(Result1, 1);
		//------------------------------------------------------------------------
		// testing the IsLetter Function to make sure it only return true for the chars that represent English letters 
		bool Result2 = true;
		for (char StrLetter : Letters)
		{
			if (IsLetter(StrLetter) == false) { Result2 = false; }
		}

		for (char StrNum : Numbers)
		{
			if (IsLetter(StrNum) == true) { Result2 = false; }
		}

		AddResult(Result2, 2);
		//------------------------------------------------------------------------
		// 
		bool Result3 = false;
		uint32_t Index = 0;
		uint32_t LineNumber = 0;
		IgnoreNewLineChar("\n\n\n\n\n", Index, LineNumber);
		if (LineNumber == 5) { Result3 = true; }

		AddResult(Result3, 3);

		// check the lexical analysis of a comment 
		//------------------------------------------------------------------------
		const char* FakeCode0 = "/*   */";
		ILexerState *ptr_commentCheck = new LexStateCommentChecker();
		ptr_commentCheck->m_refErrrorsMod = mref_Error;
		Index = 0;
		LineNumber = 0;
		std::vector<Token> tokens0;
		std::map<string, string> FakeMap0;
		bool Result4 = ptr_commentCheck->StateAction(FakeCode0, Index, LineNumber, tokens0, &FakeMap0);
		delete ptr_commentCheck;
		AddResult(Result4, 4);


		// check the lexical analysis of a string  
		//------------------------------------------------------------------------
		const char* FakeCode1 = "\" sdfdsfdsfewa49039r \" ";
		std::unique_ptr<LexStringChecker> ptr_stringCheck = std::make_unique<LexStringChecker>();
		ptr_stringCheck->m_refErrrorsMod = mref_Error;
		Index = 0;
		LineNumber = 0;
		std::vector<Token> tokens1;
		std::map<string, string> FakeMap1;
		bool Result5 = ptr_stringCheck->StateAction(FakeCode1, Index, LineNumber, tokens1, &FakeMap1);
		AddResult(Result5, 5);


	}

	void TestingClass::AddResult(bool Result, int Index)
	{
		m_Results[Index] = Result;
	}

	bool TestingClass::CheckAllTest()
	{
		for (int i = 0; i < TotalTest; ++i)
		{
			PrintToConsole(" Result of test {0}  {1}", i, m_Results[i]);
		}

		return true;
	}

}