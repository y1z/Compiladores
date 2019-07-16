#pragma once
namespace Compiler {
	/*! the type of operator the node contains*/
	enum class ExpressionNodeType
	{
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
		ExpressionNodeType m_NodeType;

		ExpLogTreeNode *m_LeftNode;
		ExpLogTreeNode *m_RightNode;

	};

}
