#pragma once
#include "LexAnalyzer.h"
#include  "ErrorsModule.h"
#include "SymbolsTable.h"

namespace Compiler {

	class SemanticAnalysis
	{
	public:
		SemanticAnalysis();
		~SemanticAnalysis();
	public://expression
		/*!
		\param [in] Expression this consist of all the tokens composing a expression
		\param [in] FunctionName to know where the expression comes from */
		void AddExplog(std::vector<Token*> Expression, std::string FunctionName);
		/*!starts the evaluation of expressions*/
		void CheckExpressions();// Main method 
	};

}