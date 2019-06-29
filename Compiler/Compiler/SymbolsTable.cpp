#include "stdafx.h"
#include "SymbolsTable.h"

namespace Compiler {

	SymbolsTable::SymbolsTable()
	{}


	SymbolsTable::~SymbolsTable()
	{
		for (auto Node : m_Symbols)
		{
			delete Node.second;
		}

	}

	void SymbolsTable::Reset()
	{
		if (!m_Symbols.empty())
		{
			m_Symbols.clear();
		}
	}

	bool SymbolsTable::SymbolExists(const std::string & Sym, SymbolCategory Cat, std::string & Function)
	{
		// find the symbol
		if (m_Symbols.find(Sym) != m_Symbols.end())
		{
			auto IsInserted = m_Symbols.find(Sym);
			// get the node that contains the value 
			GlobalNode * gNode = IsInserted->second;

			if (gNode->GetSymbolCategory() == Cat)
			{
				return true;
			}
			else// keep searching for the value 
			{
				auto it = m_Symbols.find(Sym);
				GlobalNode *gNode = it->second;
				LocalNode *lNode = gNode->GetLocalNode();
				// keep going until you cant anymore 
				while (lNode != nullptr)
				{
					if (lNode->GetSymbolCategory() == Cat && !(lNode->GetFunctionName().compare(Function)))
					{
						return true;
					}
					lNode = lNode->GetLocalNode();
				}
			}
		}

		return false;
	}// end function

	bool SymbolsTable::AddSymbol(std::string &Symbol, int dim, SymbolCategory Cat, std::string &function, std::string &Type)
	{
		if (!SymbolExists(Symbol, Cat, function))
		{

			if (Cat == SymbolCategory::global_var)
			{
				m_Symbols[Symbol] = new GlobalNode();
				m_Symbols[Symbol]->SetSymbol(Symbol.c_str());
				m_Symbols[Symbol]->SetDimension(dim);
				m_Symbols[Symbol]->SetSymbolCategory(SymbolCategory::global_var);
				m_Symbols[Symbol]->SetType(Type.c_str());
				return true;
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
		}
		else
		{
			// Add error (Symbol Already defined)
		}

		return false;
	}


}// end namespace