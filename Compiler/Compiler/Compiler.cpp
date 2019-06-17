#include "stdafx.h"
#include "Compiler.h"
#include "Utility.h"

void Compiler::Manager::StartLexAnalysis(String ^ srcCode)
{
	// here starts the parsing 
	Manager::ptr_Lex->ParseSourceCode(((const char *) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(srcCode).ToPointer()));
}

// TODO add parsing for Syntactic and semantic stages 
cli::array<String^>^ Compiler::Manager::StartDataParsing()
{
	cli::array<String^> ^CompilationDetails;

	if (ptr_Lex != nullptr)
	{
		// checks to see if there are any tokes or errors was generated 
		if (0 < (Manager::ptr_Lex->GetTokenCount() + ptr_Lex->m_refErrrorsMod->GetErrorCount()))
		{
			// the plus 1 is there because i need to reserve a spot for the parser of this data 
			uint32_t TotalSize = (ptr_Lex->GetTokenCount() + ptr_Lex->m_refErrrorsMod->GetErrorCount() + 1);
			// keeping track of where the array already has information and spot 0 is already taken 
			uint32_t CurrentPos = 0;

			CompilationDetails = gcnew cli::array<String ^>(TotalSize);

			std::string Temp;
			std::string Result = ptr_Lex->m_refErrrorsMod->GetErrorCountString(Temp);
			// to know how many errors where generated 
			CompilationDetails[0] = "#ER_";
			CompilationDetails[0] += gcnew String(Result.c_str());

			Temp.clear();
			// to know how many Tokens where generated 
			Result.clear();
			Result = ptr_Lex->GetTokenCountString(Temp);
			CompilationDetails[0] += "#LE_" + gcnew String(Result.c_str());

			for each (String^ Error in ptr_Lex->m_refErrrorsMod->getErrors())
			{
				if (Error != "")
				{
					CurrentPos++;
					CompilationDetails[CurrentPos] += Error;
				}
			}

			// get all tokens 
			for (int i = 0; i < ptr_Lex->GetTokenCount(); ++i)
			{
				CurrentPos++;
				// initialize the String 
				CompilationDetails[CurrentPos] = "";
				// converts std::string to System::String(Lexema)
				CompilationDetails[CurrentPos] = gcnew String(ptr_Lex->GetTokenContainer()[i].getLex().c_str());
				CompilationDetails[CurrentPos] += "~";
				// converts int to System::String (LineNumber )
				CompilationDetails[CurrentPos] += gcnew String(std::to_string(ptr_Lex->GetTokenContainer()[i].getLineNum()).c_str());
				CompilationDetails[CurrentPos] += "~";
				// converts enum to System::String (Type) 
				CompilationDetails[CurrentPos] += gcnew String(TranslateToken(ptr_Lex->GetTokenContainer()[i].getType()));
				CompilationDetails[CurrentPos] += "~";

				Console::WriteLine("Here are the compilation details <| {0} |>", CompilationDetails[CurrentPos]);
			}
		}
		else
		{
			CompilationDetails = gcnew cli::array<String ^>(1);
			CompilationDetails[0] = gcnew String("-------NO TOKEN GENERATED--------");
		}
	}

	return CompilationDetails;
}

Compiler::Manager::Manager()
{
	Manager::ptr_Error = gcnew ErrorsModule();
	Manager::ptr_Lex = new LexAnalyzer(ptr_Error);
	Manager::ptr_Semantic = new SemanticAnalysis();
	Manager::ptr_Table = new SymbolsTable();
	Manager::ptr_Syntax = new SyntaxAnalysis(ptr_Lex, ptr_Error, ptr_Table);
}

Compiler::Manager::~Manager()
{
	if (Manager::ptr_Lex != nullptr)
	{
		ptr_Lex->ClearToken();
		delete Manager::ptr_Lex;
	}
	if (Manager::ptr_Syntax != nullptr) { delete ptr_Syntax; }
	if (Manager::ptr_Semantic != nullptr) { delete ptr_Semantic; }
	if (Manager::ptr_Table != nullptr) { delete ptr_Table; }

}

//! Entry Point for the Complier 
cli::array<String^>^ Compiler::Manager::compileProgram(String ^ srcCode)
{
	// clear all error messages 
	ptr_Lex->m_refErrrorsMod->clearErrors();
	// clear all tokens 
	Manager::ptr_Lex->ClearToken();

	System::Console::WriteLine("Here is the Source Code {0} ", srcCode);

	// here starts the parsing 
	Manager::ptr_Lex->ParseSourceCode(((const char *) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(srcCode).ToPointer()));
	// HERE GOES SYNTAX ANALYSIS 
	ptr_Syntax->checkSyntax();

	cli::array<String^> ^CompiltionDetails = Manager::StartDataParsing();

	return CompiltionDetails;
}// end function
