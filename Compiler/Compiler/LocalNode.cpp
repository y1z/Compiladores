#include "stdafx.h"
#include "LocalNode.h"

namespace Compiler {

	LocalNode::LocalNode(){}

	LocalNode::LocalNode(uint32_t Dem, Token_Type T_type, Node * ptr_Prev)
		:Node(Dem, T_type, ptr_Prev)
	{
		this->m_nodeType = NodeType::local_var;
	}

	LocalNode::~LocalNode()
	{}

}