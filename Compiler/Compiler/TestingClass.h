#pragma once
#include "Utility.h"
#include "ErrorFunctions.h"
#include "ErrorsModule.h"// for checking the lex states 

using namespace System;
/*!
 *\brief this class will be used to test parts of the program to make sure 
 *that everything works as intended 
 */

namespace Compiler
{
	ref class TestingClass
	{
	public:
		TestingClass();

		void RunTests();

		void AddResult(bool Result, int Index);

		bool CheckAllTest();

	private:
		ErrorsModule ^ mref_Error;
		//! store all the result of the testing 
		cli::array<bool^> ^m_Results;
	};
}


