#pragma once
#include "stdafx.h"
#include <vcclr.h>
class SymbolsTable;
#include "LexAnalyzer.h"
#include "ErrorsModule.h"
#include "SymbolsTable.h"
#include "SemanticAnalysis.h"

namespace Compiler {

	class SyntaxAnalysis
	{
	public:// constructor 
		SyntaxAnalysis(LexAnalyzer* ptr_Lex, ErrorsModule ^Error, SymbolsTable *ptr_Table,SemanticAnalysis *ptr_Sematico);
		~SyntaxAnalysis();
	public:// functions 
		void checkSyntax();

	private:// variables 
		LexAnalyzer* mptr_Lex = nullptr;
		msclr::gcroot<ErrorsModule ^> mref_ErrorMod;
		SymbolsTable *mptr_Table = nullptr;
		SemanticAnalysis *mptr_Semantic = nullptr;
	};

}