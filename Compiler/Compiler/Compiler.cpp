#include "stdafx.h"
#include "Compiler.h"
#include "GlobolNames.h"
#include "Utility.h"
#include <string>
#include <queue>

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
		uint32_t LexTotalTokens = Manager::ptr_Lex->GetTokenCount();
		int64_t SynTotalSymbols = ptr_Table->TotalElementsCount();
		uint32_t ErrorTotalErrors = ptr_Lex->m_refErrrorsMod->GetErrorCount();

		// Set up the array for receiving the data 
		if (0 < (LexTotalTokens + SynTotalSymbols + ErrorTotalErrors))
		{
			// the plus 1 is there because i need to reserve a spot for the parser of this data 
			uint64_t TotalSize = (LexTotalTokens + SynTotalSymbols + ErrorTotalErrors + 1);
			// keeping track of where the array already has information and spot 0 is already taken 
			uint32_t CurrentPos = 0;

			CompilationDetails = gcnew cli::array<String ^>(TotalSize);

			std::string Result = ptr_Lex->m_refErrrorsMod->GetErrorCountString();
			// to know how many errors where generated 
			CompilationDetails[0] = "#ER_";
			CompilationDetails[0] += gcnew String(Result.c_str());
			// to know how many Tokens where generated 
			Result.clear();
			Result = ptr_Lex->GetTokenCountString();
			CompilationDetails[0] += "#LE_" + gcnew String(Result.c_str());

			Result.clear();
			Result = std::to_string(SynTotalSymbols);
			CompilationDetails[0] += "#SY_" + gcnew String(Result.c_str());

			// get all errors
			DataParsingErrors(CurrentPos, CompilationDetails);
			// get all tokens 
			DataParsingLex(CurrentPos, CompilationDetails);
			// get all Symbols 
			DataParsingSyn(CurrentPos, CompilationDetails);
		}
		else
		{
			CompilationDetails = gcnew cli::array<String ^>(1);
			CompilationDetails[0] = gcnew String("-------NO TOKEN GENERATED--------");
		}
	}

	//if (CompilationDetails[CompilationDetails->Length] == nullptr) { CompilationDetails[CompilationDetails->Length]; }

	return CompilationDetails;
}

void Compiler::Manager::DataParsingErrors(uint32_t & CurrentPos, cli::array<String^>^% ErrorInfo)
{
	for each (String^ Error in ptr_Lex->m_refErrrorsMod->getErrors())
	{
		if (Error != "")
		{
			CurrentPos++;
			ErrorInfo[CurrentPos] += Error;
		}
	}

	if (ptr_Error->IsMaxErrorReached())
	{
		String^ MaxErrors = "\r\nCompilation stopped Max Errors Reached : ";
		MaxErrors += gcnew String(std::to_string(ptr_Error->GetMaxError()).c_str());
		ErrorInfo[CurrentPos] += MaxErrors;
	}

}

void Compiler::Manager::DataParsingLex(uint32_t & CurrentPos, cli::array<String^>^% LexInfo)
{
	for (std::size_t i = 0; i < ptr_Lex->GetTokenCount(); ++i)
	{
		CurrentPos++;
		// initialize the String 
		LexInfo[CurrentPos] = "";
		// converts std::string to System::String(Lexema)
		LexInfo[CurrentPos] = gcnew String(ptr_Lex->GetTokenContainer()[i].getLex().c_str());
		LexInfo[CurrentPos] += "~";
		// converts int to System::String (LineNumber )
		LexInfo[CurrentPos] += gcnew String(std::to_string(ptr_Lex->GetTokenContainer()[i].getLineNum()).c_str());
		LexInfo[CurrentPos] += "~";
		// converts enum to System::String (Type) 
		LexInfo[CurrentPos] += gcnew String(TranslateToken(ptr_Lex->GetTokenContainer()[i].getType()));
		LexInfo[CurrentPos] += "~";
	}
}

void Compiler::Manager::DataParsingSyn(uint32_t & CurrentPos, cli::array<String^>^% Str)
{
	std::vector<string> TableInfo = ptr_Table->ComplierInfo();

	for (std::size_t i = 0; i < TableInfo.size(); ++i)
	{
		CurrentPos++;
		PrintToConsole("Table Info : {0}", TableInfo[i]);
		String ^ Result = gcnew String(TableInfo[i].c_str());
		Str[CurrentPos] += Result;
	}
}

Compiler::Manager::Manager()
{
	Manager::ptr_Error = gcnew ErrorsModule();
	Manager::ptr_Lex = new LexAnalyzer(ptr_Error);
	Manager::ptr_Semantic = new SemanticAnalysis();
	Manager::ptr_Table = new SymbolsTable();
	/// Need this for errors 
	Manager::ptr_Table->m_refError = ptr_Error;
	Manager::ptr_Syntax = new SyntaxAnalysis(ptr_Lex, ptr_Error, ptr_Table, ptr_Semantic);
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
	ptr_Table->Reset();
	// clear all error messages 
	ptr_Lex->m_refErrrorsMod->clearErrors();
	// clear all tokens 
	Manager::ptr_Lex->ClearToken();

	System::Console::WriteLine("Here is the Source Code {0} ", srcCode);

	// here starts the parsing 
	Manager::ptr_Lex->ParseSourceCode(((const char *) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(srcCode).ToPointer()));
	// HERE GOES SYNTAX ANALYSIS 
	if (!ptr_Error->IsMaxErrorReached() && ptr_Lex->GetTokenContainer().size() != 0)
	{
		ptr_Syntax->checkSyntax();
	}

	cli::array<String^> ^CompiltionDetails = Manager::StartDataParsing();

	return CompiltionDetails;
}// end function
