#pragma once
#include "Utility.h"
namespace Compiler {
	//! this will be used to hold the information needed for the expression analysis
	struct ExpLogData
	{
		uint32_t m_LineNum = 0;
		std::vector<std::size_t>	m_IndexSymbolToUpdate;
		string m_SymbolsToCheck{ "" };
		string m_FunctionName{ "" };//
		std::vector<const Token *> mptr_tokens;
	};

	//! 
	class SemanticExpLog
	{
	public:// constructor 
		SemanticExpLog(ExpLogData &Data);
		~SemanticExpLog();
	public:// functions 
		// TODO : implement 
		void BuildTree();

		void ConvertInfixToPostFix();
		std::vector<Token *> GetPostFixNotation();
		// TODO : implement 
		bool ValidateTree();
	private: // variables 
		ExpLogData m_Data;

		//std::vector<Token *> m_InfixExpression;// a + b < that's infix notation
		std::vector<Token *> m_PostfixExpression;// a b + < that's Postfix notation
	};

}