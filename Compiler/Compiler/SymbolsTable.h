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
		//! erase all the previous data 
		void Reset();
		//! adding a new symbol to the table 
		bool AddSymbol(std::string &Symbol, int dim, SymbolCategory Cat, std::string &function, std::string &Type, int LineNum);
		//! checking so see if an symbol already exist 
		bool SymbolExists(const std::string &Sym, SymbolCategory Cat, std::string &Function, int LineNum);
		//!  check if a local var has the same name as a function 
		bool IsFunctionAlreadyLocalVar(const std::string &Sym, SymbolCategory Cat,int LineNum);
		//! find out which combination of the error massage to send 
		void SameNameSymbolDeduction(const std::string &Sym, SymbolCategory Copyed, SymbolCategory Original, int LineNum);
		// ! check to see if there are duplicates of some vars 
		bool LocalSymbolsSearch(const std::string &Sym, SymbolCategory Cat, std::string &Function, int LineNum);
		//! convert the enum SymbolCategory to an equivalent string
		string TraslateSymbolCategory(SymbolCategory SymCat);
		//! returns the container for the symbols 
		std::map<std::string, Compiler::GlobalNode*> GetSymbolsTable() const;
		//! returns all the data from the nodes formated in a manner that makes it easyer to parse 
		std::vector<std::string> ComplierInfo();
	private:
		//! add a symbol 
		bool AddSymbolToMain(std::string &Symbol, int dim, SymbolCategory Cat, std::string &function, std::string &Type, int LineNum);
	public:
		//! sum of all the Global and local nodes 
		int64_t TotalElementsCount();
		//! this is for making error reports 
		msclr::gcroot<ErrorsModule^> m_refError;
	private: // variables 
		/// el string contiene el nombre del simbolo 
		std::map<std::string, Compiler::GlobalNode*> m_Symbols;
		//! this is where all the variables related with the main function
		GlobalNode * m_MainNode = nullptr;

	};

}
