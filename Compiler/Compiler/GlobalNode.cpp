#include "stdafx.h"
#include "GlobalNode.h"

namespace Compiler {

	GlobalNode::GlobalNode()
	{}

	GlobalNode::~GlobalNode()
	{
		if (mptr_LocalNode != nullptr) { delete mptr_LocalNode; }
	}

	std::string GlobalNode::GetSymblo()
	{
		return m_Symbol;
	}

	std::string GlobalNode::GetType()
	{
		return m_Type;
	}

	SymbolCategory GlobalNode::GetSymbolCategory()
	{
		return m_SymbolCategory;
	}

	int32_t GlobalNode::GetDimension()
	{
		return m_Dimension;
	}

	uint32_t GlobalNode::GetLineNum()
	{
		return this->m_LineNum;
	}

	void * GlobalNode::GetVal()
	{
		return mptr_Val;
	}

	LocalNode * GlobalNode::GetLocalNode()
	{
		return mptr_LocalNode;
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