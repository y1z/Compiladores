#pragma once
#include "stdafx.h"
/*!
This file exist so i don't miss spell anything
*/
namespace GNames {

	/// Data Parse Codes 

	//! this is the code for Parsing error 
	static constexpr const char * code_Error = "#ER_";
	//! this is the code for parsing Lexical information for the compiler 
	static constexpr const char * code_Lexical = "#LE_";
	//! this is the code for parsing Syntactic information for the compiler 
	static constexpr const char * code_Syntactic = "#SY_";
	//! this is the code for parsing Semantic information for the compiler 
	static constexpr const char * code_Semantic = "#SM_";

	///Token Types   
	static constexpr const char * t_ID = "ID";
	static constexpr const char * t_Int = "INT_NUMBER";
	static constexpr const char * t_Float = "FLOAT_NUMBER";
	static constexpr const char * t_LogConst = "LOGICAL_CONSTANT"; 
	static constexpr const char * t_ReOp = "RELATIONAL_OPERATOR";
	static constexpr const char * t_LogOp = "LOGICAL_OPERATOR";

	///KeyWords 
	static constexpr const char * k_Func = "function";
	static constexpr const char * k_Var = "var";
	static constexpr const char * k_Main= "main"; 


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