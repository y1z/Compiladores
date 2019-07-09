#include "stdafx.h"
#include "LocalNode.h"

namespace Compiler {

	LocalNode::LocalNode()
	{
		mptr_NextNode = nullptr;
		mptr_Val = nullptr;
		m_Function = "unknown Function";
		m_Type = "unknown Type";
		m_Dimension = 0;
		m_SymbolCategory = SymbolCategory::unknown;
	}

	LocalNode::~LocalNode()
	{
		if (mptr_NextNode != nullptr)
		{
			delete mptr_NextNode;
		}

	}

	std::string LocalNode::GetFunctionName()
	{
		return m_Function;
	}

	std::string LocalNode::GetType()
	{
		return m_Type;
	}

	string LocalNode::GetSymbol() const
	{
		return m_Symbol;
	}

	SymbolCategory LocalNode::GetSymbolCategory()
	{
		return m_SymbolCategory;
	}

	int32_t LocalNode::GetDimension()
	{
		return m_Dimension;
	}

	uint32_t LocalNode::GetLineNum()
	{
		return this->m_LineNum;
	}

	void * LocalNode::GetVal()
	{
		return mptr_Val;
	}

	LocalNode * LocalNode::GetLocalNode()
	{
		return mptr_NextNode;
	}

	string LocalNode::TraslateSymbolCategory(SymbolCategory SymCat)
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

	string LocalNode::GetDataForCompiler()
	{
		string Result = std::to_string(m_LineNum) + '~';

		Result += m_Symbol + '~' + this->TraslateSymbolCategory(m_SymbolCategory) + '~';

		Result += std::to_string(m_Dimension) + '~' + m_Type + '~' + m_Function;

		return Result;
	}

	void LocalNode::SetFunctionName(const char * Symblo)
	{
		m_Function = Symblo;
	}

	void LocalNode::SetSymbol(const char * Symblo)
	{
		m_Symbol = Symblo;
	}

	void LocalNode::SetType(const char * TypeName)
	{
		m_Type = TypeName;
	}

	void LocalNode::SetSymbolCategory(SymbolCategory SymbolCategory)
	{
		m_SymbolCategory = SymbolCategory;
	}

	void LocalNode::SetDimension(int32_t Dim)
	{
		m_Dimension = Dim;
	}

	void LocalNode::SetValPtr(void * ptr)
	{
		mptr_Val = ptr;
	}

	void LocalNode::SetLocalNode(LocalNode * ptr)
	{
		mptr_NextNode = ptr;
	}

	std::pair<bool, SymbolCategory> LocalNode::FindDuplicate(const std::string & Sym)
	{
		std::pair<bool, SymbolCategory> result;
		//check to see we have the same symbol 
		if (!this->m_Symbol.compare(Sym))
		{
			result.first = true;
			result.second = this->GetSymbolCategory();
			return result;
		}
		// check to see if there is another node 
		LocalNode *lNode = this->GetLocalNode();
		if (lNode != nullptr)
		{
			return this->FindDuplicate(Sym);
		}
		else
		{
			result.first = false;
			result.second = SymbolCategory::unknown;

			return result;
		}
	}

	void LocalNode::SetLineNum(uint32_t Num)
	{
		this->m_LineNum = Num;
	}

}