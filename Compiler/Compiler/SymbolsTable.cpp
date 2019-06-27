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
		// Fin the symbol
		if (m_Symbols.find(Sym) != m_Symbols.end())
		{
			auto IsInserted = m_Symbols.find(Sym);
			// get the node that contains the value 
			GlobalNode * gNode = IsInserted->second;

			if (gNode->GetSymbolCategory() == Cat)
			{
				return true;
			}
			else
			{
				auto it = m_Symbols.find(Sym);
				GlobalNode *gNode = it->second;
				LocalNode *lNode = gNode->GetLocalNode();
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


		// check to see if the symblo 
		if (Cat == SymbolCategory::global_var)
		{
			auto IsInserted = m_Symbols.find(Sym);
			GlobalNode * gNode = IsInserted->second;
			if (gNode->GetSymbolCategory() == Cat)
			{
				return true;
			}
			else
			{

			}

			if (IsInserted != m_Symbols.end())
			{
				return true;
			}
			return false;
		}
		else if (Cat == SymbolCategory::function)
		{
			auto IsInserted = m_Symbols.find(Sym);
			if (IsInserted != m_Symbols.end())
			{
				return true;
			}
			return false;
		}
		else
		{
			//search all local node's 
			for (auto Node : m_Symbols)
			{
				if (Node.second->Search(Sym))
				{
					return true;
				}
				return false;
			}
		}


		return false;
	}

	bool SymbolsTable::AddSymbol(std::string &Symbol, int dim, SymbolCategory Cat, std::string &function, std::string &Tp)
	{
		if (!SymbolExists(Symbol, Cat, function))
		{

			if (Cat == SymbolCategory::global_var)
			{
				m_Symbols[Symbol] = new GlobalNode();
				m_Symbols[Symbol]->SetSymbol(Symbol.c_str());
				m_Symbols[Symbol]->SetDimension(dim);
				m_Symbols[Symbol]->SetSymbolCategory(SymbolCategory::global_var);
				m_Symbols[Symbol]->SetType(Symbol.c_str());
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