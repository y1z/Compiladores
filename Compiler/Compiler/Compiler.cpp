#include "stdafx.h"
#include "Compiler.h"

void Compiler::Manager::LexAnalysis(String ^ srcCode)
{

	if (ptr_Lex != nullptr) {
		Manager::ptr_Lex->ParseSourceCode(((const char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(srcCode).ToPointer()));
	}

	//throw gcnew System::NotImplementedException();
}


Compiler::Manager::Manager()
{
	Manager::ptr_Error = gcnew ErrorsModule();
	Manager::ptr_Lex = new LexAnalyzer(ptr_Error);
}

Compiler::Manager::~Manager()
{
	if (Manager::ptr_Lex != nullptr) {
		delete Manager::ptr_Lex;
	}

}

//! Entry Point for the Complier 
cli::array<String^>^ Compiler::Manager::compileProgram(String ^ srcCode)
{

	cli::array<String^> ^CompiltionDetails;

	Manager::LexAnalysis(srcCode);

	CompiltionDetails = gcnew cli::array<String ^>(1);
	CompiltionDetails[0] = gcnew String("-------CompileOK--------");


	return CompiltionDetails;
}// end function
