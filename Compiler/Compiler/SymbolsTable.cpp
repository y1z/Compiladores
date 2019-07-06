#include "stdafx.h"
#include "SymbolsTable.h"
#include "ErrorFunctions.h"

using namespace std::string_literals;

namespace Compiler {

	SymbolsTable::SymbolsTable()
	{
		m_MainNode = new GlobalNode();
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

		if (m_MainNode != nullptr) { delete m_MainNode; }

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

	bool SymbolsTable::SymbolExists(const std::string & Sym, SymbolCategory Cat, std::string & Function, int LineNum)
	{
		if (!Sym.compare(Function))
		{
			string ErrorMessage{ "" };
			string Symblo(" ,Symblo : ");
			Symblo += Sym;
			switch (Cat)
			{
			case Compiler::SymbolCategory::local_var:
				ErrorMessage += "Local variable name cannot be the same as a function name ";
				m_refError->AddSynError(LineNum, ErrorMessage, Symblo);
				break;
			case Compiler::SymbolCategory::param:
				ErrorMessage += "Parameter name cannot be the same as a function name ";
				m_refError->AddSynError(LineNum, ErrorMessage, Symblo);
				break;
			}
			return true;
		}

		// Check if the symbol already exist 
		if (m_Symbols.find(Sym) != m_Symbols.end())
		{
			auto IsInserted = m_Symbols.find(Sym);
			// get the node that contains the value 
			GlobalNode * gNode = IsInserted->second;
			/// making sure we don't have to functions/global_vars with the same names 
			if (gNode->GetSymbolCategory() == Cat)
			{
				string ErrorDesc = ErrorFuncs::SYN_ALREADY_IN_SCOPE(Sym.c_str());
				m_refError->AddSynError(LineNum, ErrorDesc, "");
				return true;
			}

			else/// making dsure we don't have a local_var with the same name o
			{
				string ErrorDesc = ErrorFuncs::SYN_ALREADY_DIFINED(Cat, gNode->GetSymbolCategory());
				string DuplicateSymbol = "Symbol "s + Sym;
				m_refError->AddSynError(LineNum, ErrorDesc, DuplicateSymbol);
				return true;
			}
		}

		if (m_Symbols.find(Function) != m_Symbols.end() || !Function.compare(GNames::k_Main))
		{
			auto DefinedSymbol = m_Symbols.find(Function);
			string ErrorDecs{ 0 };

			switch (Cat)
			{
			case Compiler::SymbolCategory::unknown:
				break;
			case Compiler::SymbolCategory::global_var:

				break;
			case Compiler::SymbolCategory::local_var:
				ErrorDecs = ErrorFuncs::SYN_SAME_NAME(Cat, DefinedSymbol->second->GetSymbolCategory());
				this->m_refError->AddSynError(LineNum, ErrorDecs, "Symbol "s + Sym);
				return true;
				break;
			case Compiler::SymbolCategory::param:
				break;
			case Compiler::SymbolCategory::function:
				break;
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

	std::map<std::string, Compiler::GlobalNode*> SymbolsTable::GetSymbolsTable() const
	{
		return this->m_Symbols;
	}

	std::vector<std::string> SymbolsTable::ComplierInfo()
	{
		std::vector<string> Result;

		for (const auto &Node : this->m_Symbols)
		{
			Result.emplace_back(Node.second->GetDataForCompiler());
			LocalNode * Temp = Node.second->GetLocalNode();
			// getting the data from m_Symbols 
			while (Temp != nullptr)
			{
				Result.emplace_back(Temp->GetDataForCompiler());
				Temp = Temp->GetLocalNode();
			}

		}

		LocalNode *MainNodes = m_MainNode->GetLocalNode();
		while (MainNodes != nullptr)
		{
			Result.emplace_back(MainNodes->GetDataForCompiler());
			MainNodes = MainNodes->GetLocalNode();
		}

		return Result;
	}

	bool SymbolsTable::AddSymbolToMain(std::string &Symbol, int dim, SymbolCategory Cat, std::string &function, std::string &Type, int LineNum)
	{
		if (Cat == SymbolCategory::local_var)
		{
			bool IsSimbloDuplicate = false;
			LocalNode *ptr_Temp = m_MainNode->GetLocalNode();
			if (IsSimbloDuplicate == false)
			{
				LocalNode *ptr_lNode = new LocalNode();
				ptr_lNode->SetDimension(dim);
				ptr_lNode->SetFunctionName(function.c_str());
				ptr_lNode->SetSymbolCategory(Cat);
				ptr_lNode->SetSymbol(Symbol.c_str());
				ptr_lNode->SetType(Type.c_str());
				ptr_lNode->SetLineNum(LineNum);
				m_MainNode->AddLocalNode(ptr_lNode);
			}
		}
		return false;
	}
	// end function 
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
		// geting the node count form main node 
		LocalNode *lMainNode = m_MainNode->GetLocalNode();
		while (lMainNode != nullptr)
		{
			++Result;
			lMainNode = lMainNode->GetLocalNode();
		}

		return Result;
	}// end function

	bool SymbolsTable::AddSymbol(std::string &Symbol, int dim, SymbolCategory Cat, std::string &function, std::string &Type, int LineNum)
	{
		if (!SymbolExists(Symbol, Cat, function, LineNum))
		{
			if (!function.compare("main"))
			{
				AddSymbolToMain(Symbol, dim, Cat, function, Type, LineNum);
				return true;
			}


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
				auto IsInserted = m_Symbols.find(function);
				GlobalNode *gNode = IsInserted->second;
				LocalNode *lNode = gNode->GetLocalNode();
				if (m_Symbols.find(function) != m_Symbols.end())
				{
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
					else
					{
						ErrorFuncs::SYN_ALREADY_IN_SCOPE(Symbol.c_str());
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
	}// end function
}// end nameSpace