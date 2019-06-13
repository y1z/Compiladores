#pragma once
#include "Node.h"

namespace Compiler {

	class ParamNode :
		public Node
	{
	public:
		ParamNode();
		ParamNode(uint32_t Dem, Token_Type T_type, Node * ptr_Prev);
		~ParamNode();
	};

}