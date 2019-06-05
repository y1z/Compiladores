#pragma once

#include <vector>

using namespace System;

namespace Compiler {

#define MAX_ERRRORS 30

	public enum class ERROR_PHASE
	{
		GLOBAL,
		LEX_ANALYZER,
		SYN_ANALYZER,
		SEM_ANALYZER,
		CODE_GENERATION
	};


	public ref class ErrorsModule
	{
	public:
		ErrorsModule();
		//! use when done 
		void clearErrors();
		/*! \param [in] ErrorDesc tiene un string que describe el error*/
		bool addError(ERROR_PHASE phase, int lineNumber, String^ ErrorDesc, String ^errorLine);
		//! for lex errors 
		bool AddLexError(uint32_t LineNumber, const std::string &ErrorDesc, const std::string &OriginalErrorLine);
		//! for Syntactic errors 
		bool AddSynError(uint32_t LineNumber, const std::string &ErrorDesc, const std::string &OriginalErrorLine);
		//! for Semantic errors 
		bool AddSemError(uint32_t LineNumber, const std::string &ErrorDesc, const std::string &OriginalErrorLine);
		int GetErrorCount();
		//! this is for passing the amount of errors to a the System::String type 
		std::string GetErrorCountString(std::string &result);
		///! to return the array that contains the errors 
		cli::array<String ^> ^getErrors()
		{
			return m_errorArray;
		}
	private:
		int m_numError;
		cli::array<String^> ^m_errorArray;

	};
}


