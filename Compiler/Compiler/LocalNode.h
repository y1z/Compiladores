#pragma once
#include "Node.h"
namespace Compiler {
	class LocalNode :
		public Node
	{
	public:
		LocalNode();
		LocalNode(uint32_t Dem, Token_Type T_type, Node * ptr_Prev);
		~LocalNode();
	};

}