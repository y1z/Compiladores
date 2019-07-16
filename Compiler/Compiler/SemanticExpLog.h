#pragma once
namespace Compiler {
	class SemanticExpLog
	{
	public:// constructor 
		SemanticExpLog();
		~SemanticExpLog();
	public:// functions 
		// TODO : implement 
		void BuildTree();
		// TODO : implement 
		bool ValidateTree();
	private: // variables 
		uint32_t m_LineNum;
		string m_SymbolToCheck;
		string m_FunctionName;
		uint32_t m_SymbolIndexToUpdate;//symbol
		
		std::vector<Token *> m_InfixExpression;// a + b < that's infix notation
		std::vector<Token *> m_PostfixExpression;// a b + < that's Postfix notation
	};

}