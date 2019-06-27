#pragma once
#include "stdafx.h"
/*!
This file exist so i don't miss spell anything
*/
namespace g_Names {

	///Token names  
	static constexpr const char * t_ID = "ID";

	///KeyWords 
	static constexpr const char * k_Func = "function";

	/// Common Error messages 
	static string e_GlobalScope = "<GLOBAL SCOPE>";

	///Valid Var endings 
	// all the spellings of the keyword that can come after 'var' 
	static constexpr const char * Var_I = "int";
	static constexpr const char * Var_f = "float";
	static constexpr const char * Var_s = "string";
	static constexpr const char * Var_b = "bool";
	/*! a vector that contains all the possible spelling's  */
	static std::vector<string> AllVarAfter = { Var_I,Var_f,Var_s,Var_b };

	/// Delimiters 
	 static constexpr const char * d_LineEnd = ";";
}