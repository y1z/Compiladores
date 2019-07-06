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
		void AddExplog(std::vector<Token*> &Expression, const std::string &FunctionName);
		/*!starts the evaluation of expressions*/
		void CheckExpressions();// Main method 
		//! return the Expression Container
		std::map<const string, std::vector<Token *>> GetExpresionContainer() const;

	private:
		//! this holds the tokens and function names needed for evaluating expression 
		std::map<const string, std::vector<Token *>> m_ExpressionTokens;

	};

}