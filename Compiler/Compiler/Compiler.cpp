#include "stdafx.h"

#include "Compiler.h"
#include "ErrorsModule.h"
#include "LexAnalyzer.h"

void Compiler::Manager::LexAnalysis(String ^ srcCode)
{

	if (ptr_Lex != nullptr) {
		ptr_Lex->ParseSourceCode(((const char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(srcCode).ToPointer()));
	}

	//throw gcnew System::NotImplementedException();
}


Compiler::Manager::Manager()
{
	ptr_Error = gcnew ErrorsModule();
	ptr_Lex = new LexAnalyzer(ptr_Error);
}

Compiler::Manager::~Manager()
{
	if (ptr_Lex != nullptr) {
		delete ptr_Lex;
	}

}

// Function : return something
cli::array<String^>^ Compiler::Manager::compileProgram(String ^ srcCode)
{

	cli::array<String^> ^CompiltionDetails;

	//LexAnalysis(srcCode);

	CompiltionDetails = gcnew cli::array<String ^>(1);
	CompiltionDetails[0] = gcnew String("-------CompileOK--------");


	return CompiltionDetails;
}// end function
