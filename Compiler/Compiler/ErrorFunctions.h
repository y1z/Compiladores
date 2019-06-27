#pragma once
#include "stdafx.h"

namespace ErrorFuncs {

	static string SYN_UNEXPECTED_SYM(const char Expected[], const char WrongLex[])
	{
		string Result = "\tError Expected : '<";
		Result += Expected;
		Result += ">' but got: ";
		Result += WrongLex;
	
		return Result;
	}

	static string SYN_ALREADY_IN_SCOPE(const char Repeated[])
	{
		string Result;
		Result += "\tVariable/Function already defined in the same scope\t";
		Result += "Symbol : ";
		Result += Repeated;


		return Result;
	}

}
