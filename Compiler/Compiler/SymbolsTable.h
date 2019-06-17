#pragma once
#include <string>
#include <map>
#include "GlobalNode.h"

namespace Compiler {

	class SymbolsTable
	{
	public:
		SymbolsTable();
		~SymbolsTable();
	public: // functions 
	//	bool UpdateSymbol();
		void Reset();

		bool AddSymbol(std::string &Symbol,int dim,SymbolCategory Cat,std::string &function,std::string &Tp);
		bool SymbolExists(const std::string &Sym,SymbolCategory Cat,std::string &Function);
		//std::string getSymbolType();// needs more param's
		//std::string getSymbolScope();// needs more param's

	private: // variables 
		std::map<std::string, Compiler::GlobalNode*> m_Symbols;
	};

}
