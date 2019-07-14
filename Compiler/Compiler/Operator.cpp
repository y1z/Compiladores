#include "stdafx.h"
#include "Operator.h"

namespace Compiler {

	Operator::Operator(char ArithmeticOperator)
	{
		switch (ArithmeticOperator)
		{
		case '+':
		case '-':
			m_Order = Order::AdditionAndSubtraction;
			break;
		case '*':
		case '/':
			m_Order = Order::MultiplicationAndDivision;
			break;
		case '^':
			m_Order = Order::Exponents;
			break;
		default:
			PrintToConsole("Error unknown operator assigned ");
			m_Order = Order::UNKNOWN;
			break;
		}


	}

	Operator::~Operator()
	{}

	bool Operator::operator<(const Operator & OtherOp)
	{
		if (this->m_Order < OtherOp.m_Order)
		{
			return true;
		}

		return false;
	}

	bool Operator::operator>(const Operator & OtherOp)
	{
		if (this->m_Order > OtherOp.m_Order)
		{
			return true;
		}

		return false;
	}

	bool Operator::operator==(const Operator & OtherOp)
	{
		if (this->m_Order == OtherOp.m_Order)
		{ return true; }

		return false;
	}

}