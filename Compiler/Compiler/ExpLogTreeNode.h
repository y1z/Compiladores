#pragma once
namespace Compiler {
	/*! the type of operator the node contains*/
	enum class ExpressionTreeNodeType
	{
		NONE,
		Arithmetic,
		Logical,
		Relational
	};


	class ExpLogTreeNode
	{
	public:
		ExpLogTreeNode();
		~ExpLogTreeNode();
	public:
		
	private:
		ExpressionTreeNodeType m_NodeType;

		ExpLogTreeNode *m_LeftNode;
		ExpLogTreeNode *m_RightNode;

	};

}
