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
		void clearErrors();
		/*! \param [in] ErrorDesc tiene un string que describe el error*/
		bool addError(ERROR_PHASE phase, int lineNumber, String^ ErrorDesc, String ^errorLine);
		cli::array<String ^> ^getErrors()
		{
			return m_errorArray;
		}
		bool AddLexError(uint32_t LineNumber, const std::string &ErrorDesc, const std::string &OriginalErrorLine);
		bool AddSynError(uint32_t LineNumber, const std::string &ErrorDesc, const std::string &OriginalErrorLine);
		bool AddSemError(uint32_t LineNumber, const std::string &ErrorDesc, const std::string &OriginalErrorLine);
	private:
		int m_numError;
		cli::array<String^> ^m_errorArray;

	};
}


