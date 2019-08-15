#pragma once
class ExpLogTreeNode;

namespace Compiler {
	/*! the start of the tree */
	class ExpLog
	{
	public:
		ExpLog();
		~ExpLog();
		
		ExpLogTreeNode *mptr_RootNode;
	};

}