#include "stdafx.h"
#include "SyntaxAnalysis.h"
#include "SynStateProgram.h"


Compiler::SyntaxAnalysis::SyntaxAnalysis()
{

}

Compiler::SyntaxAnalysis::SyntaxAnalysis(LexAnalyzer * ptr_Lex, ErrorsModule ^ Error, SymbolsTable * ptr_Table, SemanticAnalysis *ptr_Sematico)
{
	this->mptr_Lex = ptr_Lex;
	this->mref_ErrorMod = Error;
	this->mptr_Table = ptr_Table;
	this->mptr_Semantic = ptr_Sematico;
}

Compiler::SyntaxAnalysis::~SyntaxAnalysis()
{

}

void Compiler::SyntaxAnalysis::checkSyntax()
{
	ISynState* ptr_Program = new SynStateProgram(mptr_Lex,this,nullptr,mptr_Table,mptr_Semantic);
	ptr_Program->CheckSyntax();
	//ISyntaxState *ptr_Program = new SyntaxState_Program();
	//ptr_Program->InitState(mptr_Lex, this, nullptr, mptr_Table);
	//ptr_Program->CheckSyntax();
	delete ptr_Program;
}

