#include "stdafx.h"
#include "GlobalNode.h"

namespace Compiler {

	GlobalNode::GlobalNode()
	{}

	GlobalNode::~GlobalNode()
	{}

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

	uint32_t GlobalNode::GetDimension()
	{
		return m_Dimension;
	}

	void * GlobalNode::GetVal()
	{
		return mptr_Val;
	}

	LocalNode * GlobalNode::GetLocalNode()
	{
		return mptr_LocalNode;
	}
	
	//--------------------- SETTERS--------------
	void GlobalNode::SetSymbol(const char * Symblo)
	{ m_Symbol = Symblo; }

	void GlobalNode::SetType(const char * TypeName)
	{ m_Type = TypeName; }

	void GlobalNode::SetSymbolCategory(SymbolCategory SymbolCategory)
	{ m_SymbolCategory = SymbolCategory; }

	void GlobalNode::SetDimension(uint32_t Dim)
	{ m_Dimension = Dim; }

	void GlobalNode::SetValPtr(void * ptr)
	{ mptr_Val = ptr; }

	void GlobalNode::SetLocalNode(LocalNode * ptr)
	{ mptr_LocalNode = ptr; }
}