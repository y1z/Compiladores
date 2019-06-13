#pragma once
//class LexAnalyzer;
ref class ErrorsModule;

#include"Usable_Windows.h"
#include "LexAnalyzer.h"
#include "SymblosTable.h"
#include "SemanticAnalysis.h"
#include "SyntaxAnalysis.h"
#include "ErrorsModule.h"

using namespace System;

namespace Compiler {
	// ref significa que sera una clase manejada (se limpia la memoria por me) 

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
		SymblosTable *ptr_Table = nullptr;
		LexAnalyzer *ptr_Lex = nullptr;

		cli::array<String^ > ^compileProgram(String^ srcCode);
	};

};


