#include "stdafx.h"
#include "GlobalNode.h"

namespace Compiler {

	GlobalNode::GlobalNode()
	{}

	GlobalNode::~GlobalNode()
	{
		if (mptr_LocalNode != nullptr) { delete mptr_LocalNode; }
	}

	std::string GlobalNode::GetSymblo()const
	{
		return m_Symbol;
	}

	std::string GlobalNode::GetType() const
	{
		return m_Type;
	}

	SymbolCategory GlobalNode::GetSymbolCategory()const
	{
		return m_SymbolCategory;
	}

	int32_t GlobalNode::GetDimension()const
	{
		return m_Dimension;
	}

	uint32_t GlobalNode::GetLineNum()const
	{
		return this->m_LineNum;
	}

	void * GlobalNode::GetVal()
	{
		return mptr_Val;
	}

	LocalNode * GlobalNode::GetLocalNode()const
	{
		return mptr_LocalNode;
	}

	string GlobalNode::TraslateSymbolCategory(SymbolCategory SymCat)
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
			return string();
		}
	}

	string GlobalNode::GetDataForCompiler()
	{
		string Result = std::to_string(m_LineNum) + '~';

		Result += m_Symbol + '~' + this->TraslateSymbolCategory(m_SymbolCategory) + '~';

		Result += std::to_string(m_Dimension) + '~' + m_Type + '~' + "<GLOBAL SCOPE>";

		return Result;
	}

	void GlobalNode::AddLocalNode(LocalNode * Node)
	{
		// use this one to travers the local nodes 
		LocalNode* Temp = nullptr;
		if ((Temp = this->GetLocalNode()) == nullptr)
		{
			this->SetLocalNode(Node);
		}
	
		else
		{
			LocalNode* PrevTemp = Temp;
			while (Temp != nullptr)
			{
				PrevTemp = Temp;
				Temp = Temp->GetLocalNode();
			}
			PrevTemp->SetLocalNode(Node);
		}

	}

	bool GlobalNode::Search(const string &Ref)
	{
		LocalNode * ptr_NextNode = this->GetLocalNode();
		while (ptr_NextNode != nullptr)
		{
			if (!Ref.compare(ptr_NextNode->GetFunctionName()))
			{
				return true;
			}
			ptr_NextNode = this->GetLocalNode();
		}

		return false;
	}

	//--------------------- SETTERS--------------
	void GlobalNode::SetSymbol(const char * Symblo)
	{ m_Symbol = Symblo; }

	void GlobalNode::SetType(const char * TypeName)
	{ m_Type = TypeName; }

	void GlobalNode::SetSymbolCategory(SymbolCategory SymbolCategory)
	{ m_SymbolCategory = SymbolCategory; }

	void GlobalNode::SetDimension(int32_t Dim)
	{ m_Dimension = Dim; }

	void GlobalNode::SetValPtr(void * ptr)
	{ mptr_Val = ptr; }

	void GlobalNode::SetLocalNode(LocalNode * ptr)
	{ mptr_LocalNode = ptr; }

	void GlobalNode::SetLineNum(uint32_t Num)
	{
		this->m_LineNum = Num;
	}
}