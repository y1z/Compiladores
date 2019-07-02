#include "stdafx.h"
#include "ErrorsModule.h"
#include <string>

Compiler::ErrorsModule::ErrorsModule()
{
	m_numError = 0;
	m_errorArray = gcnew cli::array<String ^>(MAX_ERRRORS);

	for (int i = 0; i < MAX_ERRRORS; ++i)
	{
		m_errorArray[i] = gcnew String("");
	}

}

void Compiler::ErrorsModule::clearErrors()
{
	for (int i = 0; i < MAX_ERRRORS; ++i)
	{
		m_errorArray[i] = "";
	}

	m_numError = 0;
}

// check if there is less than 30 errors
bool Compiler::ErrorsModule::addError(ERROR_PHASE phase, int LineNumber, String ^ ErrorDesc, String ^ errorLine)
{
	if (m_numError < (MAX_ERRRORS ))
	{
		m_errorArray->SetValue(String::Format("{0} :\t{1} \t{2}\t{3}", phase.ToString(), LineNumber, ErrorDesc, errorLine), m_numError);
		m_numError++;
		return true;
	}
	return false;
}

bool Compiler::ErrorsModule::AddLexError(uint32_t LineNumber, const std::string &ErrorDesc, const std::string &OriginalErrorLine)
{
	ERROR_PHASE LexError = ERROR_PHASE::LEX_ANALYZER;

	String^ ErrorDescConverted = gcnew String(ErrorDesc.c_str());
	String^ ErrorLineConverted = gcnew String(OriginalErrorLine.c_str());

	return addError(LexError, LineNumber, ErrorDescConverted, ErrorLineConverted);
}

bool Compiler::ErrorsModule::AddSynError(uint32_t LineNumber, const std::string & ErrorDesc, const std::string & OriginalErrorLine)
{
	ERROR_PHASE SynError = ERROR_PHASE::SYN_ANALYZER;

	String^ ErrorDescConverted = gcnew String(ErrorDesc.c_str());
	String^ ErrorLineConverted = gcnew String(OriginalErrorLine.c_str());

	return addError(SynError, LineNumber, ErrorDescConverted, ErrorLineConverted);
}

bool Compiler::ErrorsModule::AddSemError(uint32_t LineNumber, const std::string & ErrorDesc, const std::string & OriginalErrorLine)
{
	ERROR_PHASE SemError = ERROR_PHASE::SEM_ANALYZER;

	String^ ErrorDescConverted = gcnew String(ErrorDesc.c_str());
	String^ ErrorLineConverted = gcnew String(OriginalErrorLine.c_str());

	return addError(SemError, LineNumber, ErrorDescConverted, ErrorLineConverted);
}

int Compiler::ErrorsModule::GetErrorCount()
{
	return m_numError;
}

bool Compiler::ErrorsModule::IsMaxErrorReached()
{
	if (m_numError < MAX_ERRRORS - 1)
	{
		return false;
	}

	return true;
}


std::string Compiler::ErrorsModule::GetErrorCountString()
{
	std::string Result = std::to_string(m_numError);

	return Result;
}

int Compiler::ErrorsModule::GetMaxError()
{
	return MAX_ERRRORS;
}