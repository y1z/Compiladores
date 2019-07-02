#pragma once
ref class ErrorsModule;

#include "Usable_Windows.h"
#include "LexAnalyzer.h"
#include "SymbolsTable.h"
#include "SemanticAnalysis.h"
#include "SyntaxAnalysis.h"
#include "ErrorsModule.h"
#include <queue>

using namespace System;

namespace Compiler {

	public ref class Manager
	{
	private:
		void StartLexAnalysis(String ^srcCode);

		//! returns all important info for the Compiler to later present to the user 
		cli::array<String^ > ^ StartDataParsing();
		//! Here we insert the Errors int the arrary<String^>^ 
		void	DataParsingErrors(uint32_t &CurrentPos, cli::array<String ^>^ %Str);
		//! Here we insert the Lexical info generated from the tokens 
		void  DataParsingLex(uint32_t &CurrentPos,cli::array<String ^>^ %Str);
		//! Get  all the info from the symbols table 
		void 	DataParsingSyn(uint32_t &CurrentPos, cli::array<String ^>^ %Str);

	public:
		Manager();
		~Manager();

		ErrorsModule ^ ptr_Error;
		SyntaxAnalysis *ptr_Syntax = nullptr;
		SemanticAnalysis *ptr_Semantic = nullptr;
		SymbolsTable *ptr_Table = nullptr;
		LexAnalyzer *ptr_Lex = nullptr;

		cli::array<String^ > ^compileProgram(String^ srcCode);
	};

};


