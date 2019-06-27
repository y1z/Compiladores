#include "stdafx.h"
#include "LocalNode.h"

namespace Compiler {

	LocalNode::LocalNode()
	{}

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

	uint32_t LocalNode::GetDimension()
	{
		return m_Dimension;
	}

	void * LocalNode::GetVal()
	{
		return mptr_Val;
	}

	LocalNode * LocalNode::GetLocalNode()
	{
		return mptr_NextNode;
	}

	void LocalNode::SetSymbol(const char * Symblo)
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

	void LocalNode::SetDimension(uint32_t Dim)
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

}