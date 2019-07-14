#pragma once
#include "stdafx.h"

/*!
\brief the purpose of this class is to know which of the operation should go first 
*/

namespace Compiler {

	enum class Order : int8_t
	{
		UNKNOWN = -1,
		AdditionAndSubtraction = 0,
		MultiplicationAndDivision = 1,
		Exponents = 2
	};


	class Operator
	{
	public:
		Operator(char ArithmeticOperator);
		~Operator();

		// relational comparison 
		bool operator < (const Operator& OtherOp);
		bool operator > (const Operator& OtherOp);
		bool operator == (const Operator& OtherOp);
	private:
		Order m_Order;

	};

}