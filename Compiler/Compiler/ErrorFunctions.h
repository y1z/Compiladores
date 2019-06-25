#pragma once
#include "stdafx.h"

namespace ErrorFuncs {

	static string SYN_UNEXPECTED_SYM(const char Expected[], const char WrongLex[])
	{
		string Result = "Error Expected : '<";
		Result += Expected;
		Result += ">' but got: ";
		Result += WrongLex;
		return Result;
	}


}
