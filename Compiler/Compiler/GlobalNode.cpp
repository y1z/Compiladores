#include "stdafx.h"
#include "GlobalNode.h"

namespace Compiler {

	GlobalNode::GlobalNode()
	{
		this->m_nodeType = NodeType::global_var;
	}

	GlobalNode::GlobalNode(uint32_t Dem, Token_Type T_type, Node * ptr_Prev)
		:Node(Dem, T_type, ptr_Prev)
	{
		this->m_nodeType = NodeType::global_var;
	}


	GlobalNode::~GlobalNode()
	{}


}