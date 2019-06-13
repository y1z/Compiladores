#pragma once
#include <string>
#include <map>
#include "AllNodes.h"

namespace Compiler {
	class SymblosTable
	{
	public:
		SymblosTable();
		~SymblosTable();

	public: // functions 
		bool UpdateSymbol();
		void Reset();

		bool AddSymbol();
		bool boolSymbolExists();
		std::string getSymbolType();// needs more param's
		std::string getSymbolScope();// needs more param's

	private: // variables 
		std::map<std::string, GlobalNode*> m_Symbols;

	};
}