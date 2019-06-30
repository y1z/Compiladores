#pragma once
#include "stdafx.h"
/*!
This file exist so i don't miss spell anything
*/
namespace g_Names {

	///Token Types   
	static constexpr const char * t_ID = "ID";
	static constexpr const char * t_Int = "INT_NUMBER";

	///KeyWords 
	static constexpr const char * k_Func = "function";

	///  messages 
	static string GlobalScope = "<GLOBAL SCOPE>";

	///Valid Var endings 
	// all the spellings of the keyword that can come after 'Value' 
	static constexpr const char * Value_i = "int";
	static constexpr const char * Value_f = "float";
	static constexpr const char * Value_s = "string";
	static constexpr const char * Value_b = "bool";
	/*! a vector that contains all the correct values a var can be */
	static std::vector<string> AllVarAfter = { Value_i,Value_f,Value_s,Value_b };

	/// Data Types 
	static constexpr const char * AllTypes = "'<int>|<float>|<string>|<bool>|<void>'";
	/// Delimiters 
	 static constexpr const char * d_LineEnd = ";";
}