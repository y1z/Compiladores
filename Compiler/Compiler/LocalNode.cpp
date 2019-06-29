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

	void LocalNode::SetFunctionName(const char * Symblo)
	{
		m_Function = Symblo;
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

	void LocalNode::SetLineNum(uint32_t Num)
	{
		this->m_LineNum = Num;
	}

}