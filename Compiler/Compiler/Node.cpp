#include "stdafx.h"
#include "Node.h"


namespace Compiler {

	Node::Node()
	{}

	Node::Node(uint32_t Dem, Token_Type T_type, Node * ptr_Prev)
	{
		this->m_Dimension = Dem;
		this->m_TokenType = T_type;
		this->mptr_PrevNode = ptr_Prev;
	}


	Node::~Node()
	{}

	Node * Node::GetNextNode()
	{
		return this->mptr_NextNode;
	}

	Node * Node::GetPrevNode()
	{
		return mptr_PrevNode;
	}

	uint32_t Node::GetDimension()
	{
		return m_Dimension;
	}

	Token_Type Node::GetNodeType()
	{
		return this->m_TokenType;
	}

	const char * Node::GetValue()
	{
		return mptr_Value->c_str();
	}

	void Node::SetDimenstion(uint32_t dem)
	{
		this->m_Dimension = dem;
	}

	void Node::SetNextNode(Node * ptr)
	{
		this->mptr_NextNode = ptr;
	}

	void Node::SetPrevNode(Node * ptr)
	{
		this->mptr_PrevNode = ptr;
	}

	void Node::SetTokenType(Token_Type type)
	{
		this->m_TokenType = type;
	}
	//
	void Node::SetNodeType(NodeType nodeType)
	{
		this->m_nodeType = nodeType;
	}

	void Node::SetValue(const std::string & Str)
	{
		mptr_Value = &Str;
	}

}