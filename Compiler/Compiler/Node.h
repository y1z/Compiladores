#pragma once
#include "Token.h"

namespace Compiler {
	/*! this is used to determinate which
	value, function the node will hold */
	enum class NodeType
	{
		unknown,
		global_var,
		local_var,
		param,
		function
	};

};

/*!
\brief Here is the base class for all node Classes
*/

namespace Compiler {
	class Node
	{
	public:
		Node();
		Node(uint32_t Dem, Token_Type T_type, Node *ptr_Prev = nullptr);
		virtual ~Node();
	public: // function 
		// all getters 
		Node *GetNextNode();
		Node *GetPrevNode();
		uint32_t GetDimension();
		Token_Type GetNodeType();
		const char * GetValue();


		// all setters 
		void SetDimenstion(uint32_t dem);
		void SetNextNode(Node *ptr);
		void SetPrevNode(Node *ptr);
		void SetTokenType(Token_Type type);
		void SetNodeType(NodeType nodeType);
		void SetValue(const std::string &Str);


	protected: // variable
		NodeType m_nodeType;
		Token_Type m_TokenType = Token_Type::UNDEFINED;
		std::string const *mptr_Value = nullptr;

		uint32_t m_Dimension = 1;

		Node * mptr_NextNode = nullptr;
		Node * mptr_PrevNode = nullptr;
	};
};
