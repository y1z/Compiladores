#pragma once
#include "stdafx.h"
#include <vcclr.h>
class SymbolsTable;
#include "LexAnalyzer.h"
#include "ErrorsModule.h"
#include "SymbolsTable.h"


//ref class ErrorsModule;
//class LexAnalyzer;
//class SyntaxState_Function;
//
namespace Compiler {

	class SyntaxAnalysis
	{
	public:// constructor 
		SyntaxAnalysis();
		SyntaxAnalysis(LexAnalyzer* ptr_Lex, ErrorsModule ^Error, SymbolsTable *ptr_Table);
		~SyntaxAnalysis();
	public:// functions 
		void checkSyntax();

	private:// variables 

		LexAnalyzer* mptr_Lex = nullptr;
		msclr::gcroot<ErrorsModule ^> mref_ErrorMod;
		SymbolsTable *mptr_Table = nullptr;

	};

}