#pragma once
class ExpLogTree;

//TODO : add member 'ExpLogTree *m_Node'
namespace Compiler {
	class ExpLog
	{
	public:
		ExpLog();
		~ExpLog();
		
		ExpLogTree *mptr_Node;
	};

}