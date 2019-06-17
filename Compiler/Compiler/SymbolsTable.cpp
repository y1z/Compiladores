#include "stdafx.h"
#include "SymbolsTable.h"

namespace Compiler {

	SymbolsTable::SymbolsTable()
	{}


	SymbolsTable::~SymbolsTable()
	{}

	void SymbolsTable::Reset()
	{
		if (!m_Symbols.empty())
		{
			m_Symbols.clear();
		}
	}

	bool SymbolsTable::SymbolExists(const std::string & Sym, SymbolCategory Cat, std::string & Function)
	{
		return false;
	}

	bool SymbolsTable::AddSymbol(std::string & Symbol, int dim, SymbolCategory Cat, std::string & function, std::string & Tp)
	{
		if (!SymbolExists(Symbol, Cat, function))
		{

			if (Cat == SymbolCategory::global_var)
			{
				/*Verify that does not exist as function(call symbol Exist as specific word)
					error*/
			}

			if (Cat == SymbolCategory::function)
			{
				/*Verify that does not exist as globla var
					error*/
			}

			if (Cat == SymbolCategory::local_var)
			{
				/*Verify that does not exist as parameter of the same function
				and named as function error*/
			}

			if (Cat == SymbolCategory::param)
			{
				//	Verify that does not exist as local var and not named as function
					//	error
			}

			else
			{
				// Add error (Symbol Already defined)
			}

		}
		return false;
	}

}// end namespace