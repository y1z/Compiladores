#include "stdafx.h"
#include "SyntaxAnalysis.h"
#include "ErrorFunctions.h"
#include "SynStateProgram.h"


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

	ISynState* ptr_Program = new SynStateProgram(mptr_Lex, this, nullptr, mptr_Table, mptr_Semantic);
	//  checking for symbols after main 
	ptr_Program->CheckSyntax();
	const Token *Temp = nullptr;
	if (MoveAndAssignTokenIndex(mptr_Lex, Temp))
	{
		string ErrorDesc = ErrorFuncs::SYN_PROGRAM_FINISHED(Temp->getLex().c_str());
		mptr_Lex->m_refErrrorsMod->AddSynError(Temp->getLineNum(), ErrorDesc, "");
	}
	delete ptr_Program;
}
