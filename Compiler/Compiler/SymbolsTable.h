#pragma once
#include <vcclr.h>
#include <string>
#include <map>
#include "GlobalNode.h"
#include "Token.h"
#include "ErrorsModule.h"

namespace Compiler {

	class SymbolsTable
	{
	public:
		SymbolsTable();
		~SymbolsTable();
	public: // functions 
	//	bool UpdateSymbol();
		void Reset();

		bool AddSymbol(std::string &Symbol, int dim, SymbolCategory Cat, std::string &function, std::string &Type, int LineNum);
		bool SymbolExists(const std::string &Sym,SymbolCategory Cat,std::string &Function,int LineNum);
		string TraslateSymbolCategory(SymbolCategory SymCat);
		
		//! sum of all the Global and local nodes 
		int64_t TotalElementsCount();
		//std::string getSymbolType();// needs more param's
		//std::string getSymbolScope();// needs more param's


		msclr::gcroot<ErrorsModule^> m_refError;
	private: // variables 
		/// el string contiene el nombre del simbolo 
		std::map<std::string, Compiler::GlobalNode*> m_Symbols;

	};

}
