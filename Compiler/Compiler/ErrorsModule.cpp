#include "stdafx.h"
#include "ErrorsModule.h"

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
//	throw gcnew System::NotImplementedException();
}

bool Compiler::ErrorsModule::addError(ERROR_PHASE phase, int lineNumber, String ^ ErrorDesc, String ^ errorLine)
{
	if (m_numError < (MAX_ERRRORS - 1))
	{
		m_errorArray->SetValue(String::Format("{0} : {1} {2} {3}", phase.ToString(), lineNumber, ErrorDesc, errorLine), m_numError);
	}

	return false;
}
