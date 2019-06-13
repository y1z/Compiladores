#pragma once
#include "Node.h"
namespace Compiler {

	class GlobalNode :
		public Node
	{
	public:
		GlobalNode();
		GlobalNode(uint32_t Dem, Token_Type T_type, Node * ptr_Prev);
		~GlobalNode();

	};

}