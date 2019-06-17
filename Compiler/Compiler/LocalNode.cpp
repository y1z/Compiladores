#include "stdafx.h"
#include "LocalNode.h"

namespace Compiler {

	std::string LocalNode::GetSymblo()
	{
		return m_Symbol;
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