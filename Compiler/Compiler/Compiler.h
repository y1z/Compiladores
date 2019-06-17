#pragma once
ref class ErrorsModule;

#include "Usable_Windows.h"
#include "LexAnalyzer.h"
#include "SymbolsTable.h"
#include "SemanticAnalysis.h"
#include "SyntaxAnalysis.h"
#include "ErrorsModule.h"

using namespace System;

namespace Compiler {

	public ref class Manager
	{
	private:
		void StartLexAnalysis(String ^srcCode);

		cli::array<String^ > ^ StartDataParsing();
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


