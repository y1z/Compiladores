#pragma once
#include "LexAnalyzer.h"
#include "ErrorsModule.h"
#include "SymblosTable.h"
#include "ISyntaxState.h"

namespace Compiler {

	public class SyntaxAnalysis
	{
	public:// constructor 
		SyntaxAnalysis(LexAnalyzer* ptr_Lex, ErrorsModule ^Error, SymblosTable *ptr_Table);
		~SyntaxAnalysis();
	public:// functions 
		void checkSyntax();//

	private:// variables 
		LexAnalyzer* mptr_Lex = nullptr;
		msclr::gcroot<ErrorsModule ^> mref_ErrorMod;
		SymblosTable *mptr_Table = nullptr;
//		ISyntaxState *mptr_InitState = nullptr;
	};

}