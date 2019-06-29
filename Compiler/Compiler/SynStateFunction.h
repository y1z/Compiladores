#pragma once
#include "ISynState.h"
namespace Compiler {
	class SynStateFunction : public ISynState
	{
	public:
		SynStateFunction(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic);
		~SynStateFunction();
	public:// funcions 
		bool CheckSyntax()override;
		bool CheckFunctionType();
		bool CheckFunctionBlock();
	public:// variables 
		//! To Indicate if the syntax is still valid 
		bool isValid = true;
		//! to keep track of what function I'm using 
		string m_FunctionName = "";
		//!
		bool isInFunctionBlock = false;
	};

}