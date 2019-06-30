#include "stdafx.h"
#include "SymbolsTable.h"

namespace Compiler {

	SymbolsTable::SymbolsTable()
	{
	}


	SymbolsTable::~SymbolsTable()
	{
		if (!m_Symbols.empty())
		{
			for (auto &Node : m_Symbols)
			{
				delete Node.second;
				Node.second = nullptr;
			}
			m_Symbols.clear();
		}

	}

	void SymbolsTable::Reset()
	{
		if (!m_Symbols.empty())
		{
			for (auto &Node : m_Symbols)
			{
				delete Node.second;
				Node.second = nullptr;
			}
			m_Symbols.clear();
		}
	}

	bool SymbolsTable::SymbolExists(const std::string & Sym, SymbolCategory Cat, std::string & Function,int LineNum)
	{
		if (!Sym.compare(Function))
		{
			string ErrorMessage{ "" };
			
			string Symblo = " ,Symblo : "; 
			Symblo += Sym;
			switch (Cat)
			{
			case Compiler::SymbolCategory::local_var:
				ErrorMessage += "Local variable name cannot be the same as the function name ";

				m_refError->AddSynError(LineNum, ErrorMessage, Symblo);
				break;

			case Compiler::SymbolCategory::param:
				ErrorMessage += "Parameter name cannot be the same as a function ";
				m_refError->AddSynError(LineNum, ErrorMessage, Symblo);
				break;
			}
			return true;

		}

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
	}

	string SymbolsTable::TraslateSymbolCategory(SymbolCategory SymCat)
	{
		switch (SymCat)
		{
		case Compiler::SymbolCategory::unknown:
			return "<unknown>";
			break;
		case Compiler::SymbolCategory::global_var:
			return "<GLOBAL_VAR>";
			break;
		case Compiler::SymbolCategory::local_var:
			return "<LOCAL_VAR>";
			break;
		case Compiler::SymbolCategory::param:
			return "<PARAM>";
			break;
		case Compiler::SymbolCategory::function:
			return "<FUNCTION>";
			break;
		default:
			break;
		}

		return string();
	}

	int64_t SymbolsTable::TotalElementsCount()
	{
		int64_t Result = 0;
		LocalNode *lNode = nullptr;
		for (const auto &Globalnode : m_Symbols)
		{
			lNode = Globalnode.second->GetLocalNode();
			while (lNode != nullptr)
			{
				++Result;
				lNode = lNode->GetLocalNode();
			}
			++Result;
		}

		return Result;
	}
	// end function

	bool SymbolsTable::AddSymbol(std::string &Symbol, int dim, SymbolCategory Cat, std::string &function, std::string &Type, int LineNum)
	{
		if (!SymbolExists(Symbol, Cat, function,LineNum))
		{

			if (Cat == SymbolCategory::global_var)
			{
				m_Symbols[Symbol] = new GlobalNode();
				m_Symbols[Symbol]->SetSymbol(Symbol.c_str());
				m_Symbols[Symbol]->SetDimension(dim);
				m_Symbols[Symbol]->SetSymbolCategory(SymbolCategory::global_var);
				m_Symbols[Symbol]->SetType(Type.c_str());
				m_Symbols[Symbol]->SetLineNum(LineNum);
				return true;
			}

			if (Cat == SymbolCategory::function)
			{
				m_Symbols[Symbol] = new GlobalNode();
				m_Symbols[Symbol]->SetSymbol(Symbol.c_str());
				m_Symbols[Symbol]->SetDimension(dim);
				m_Symbols[Symbol]->SetSymbolCategory(SymbolCategory::function);
				m_Symbols[Symbol]->SetType(Type.c_str());
				m_Symbols[Symbol]->SetLineNum(LineNum);
				return true;
			}

			if (Cat == SymbolCategory::local_var)
			{
				bool IsSimbloDuplicate = false;
				if (m_Symbols.find(function) != m_Symbols.end())
				{
					auto IsInserted = m_Symbols.find(function);
					GlobalNode *gNode = IsInserted->second;
					LocalNode *lNode = gNode->GetLocalNode();
					// go through all nodes 
					while (lNode != nullptr)
					{
						if (!lNode->GetSymbol().compare(Symbol))
						{
							IsSimbloDuplicate = true;
						}
						lNode = lNode->GetLocalNode();

					}
					if (IsSimbloDuplicate == false)
					{
						LocalNode *ptr_lNode = new LocalNode();
						ptr_lNode->SetDimension(dim);
						ptr_lNode->SetFunctionName(function.c_str());
						ptr_lNode->SetSymbolCategory(Cat);
						ptr_lNode->SetSymbol(Symbol.c_str());
						ptr_lNode->SetType(Type.c_str());
						ptr_lNode->SetLineNum(LineNum);
						
						gNode->AddLocalNode(ptr_lNode);
					}

				}

			}

			if (Cat == SymbolCategory::param)
			{
				bool IsSimbloDuplicate = false;
				if (m_Symbols.find(function) != m_Symbols.end())
				{
					auto IsInserted = m_Symbols.find(function);
					GlobalNode *gNode = IsInserted->second;
					LocalNode *lNode = gNode->GetLocalNode();
					// go through all nodes 
					while (lNode != nullptr)
					{
						if (!lNode->GetSymbol().compare(Symbol))
						{
							IsSimbloDuplicate = true;
						}
						lNode = lNode->GetLocalNode();

					}
					if (IsSimbloDuplicate == false)
					{
						LocalNode *ptr_lNode = new LocalNode();
						ptr_lNode->SetDimension(dim);
						ptr_lNode->SetFunctionName(function.c_str());
						ptr_lNode->SetSymbolCategory(Cat);
						ptr_lNode->SetSymbol(Symbol.c_str());
						ptr_lNode->SetType(Type.c_str());
						ptr_lNode->SetLineNum(LineNum);

						gNode->AddLocalNode(ptr_lNode);
					}

				}
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