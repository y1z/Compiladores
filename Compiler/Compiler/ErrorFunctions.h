#pragma once
#include "stdafx.h"
#include "GlobolNames.h"

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

	static string SYN_ALREADY_DIFINED(Compiler::SymbolCategory Original, Compiler::SymbolCategory Duplacate)
	{
		string Result{ "" };
		if (Original == Compiler::SymbolCategory::function) { Result += GNames::k_Func; }
		else if (Original == Compiler::SymbolCategory::local_var) { Result += "Local Var"; }
		else if (Original == Compiler::SymbolCategory::global_var) { Result += GNames::GLO_VAR; }

		Result += " already defined as ";

		if (Duplacate == Compiler::SymbolCategory::function) { Result += GNames::k_Func; }
		else if (Duplacate == Compiler::SymbolCategory::local_var) { Result += "Local Var"; }
		else if (Original == Compiler::SymbolCategory::param) { Result += GNames::GLO_VAR; }
		return Result;
	}

	static string SYN_SAME_NAME(Compiler::SymbolCategory Original, Compiler::SymbolCategory Duplacate)
	{
		string Result{ "" };
		if (Original == Compiler::SymbolCategory::function) { Result += GNames::k_Func; }
		else if (Original == Compiler::SymbolCategory::local_var) { Result += "Local Var"; }
		else if (Original == Compiler::SymbolCategory::param) { Result += "parameter"; }
		else if (Original == Compiler::SymbolCategory::global_var) { Result += GNames::GLO_VAR; }

		Result += " name cannot be the same as a ";

		if (Duplacate == Compiler::SymbolCategory::function) { Result += GNames::k_Func; }
		else if (Duplacate == Compiler::SymbolCategory::local_var) { Result += "Local Var"; }
		else if (Duplacate == Compiler::SymbolCategory::global_var) { Result += GNames::GLO_VAR; }
		else if (Duplacate == Compiler::SymbolCategory::param) { Result += "param"; }

		return Result;
	}

	static string SYN_EXPO_EXPECTED(const std::vector<char> &Parenthesis)
	{
		string Result = "Closing parenthesis expected while processing EXP_LOG : ";

		for (const char& chr : Parenthesis)
		{
			Result += chr;
		}

		return Result;
	}

	static string SYN_PROGRAM_FINISHED( const char* UnExpected)
	{
		string Result = "Error: <PROGRAM> state finished processing. No more tokens expected, but got ";
		Result += UnExpected;
		return Result;
	}
}
