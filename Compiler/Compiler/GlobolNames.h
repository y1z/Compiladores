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
	static constexpr const char  code_Syntactic[] = "#SY_";
	//! this is the code for parsing Semantic information for the compiler 
	static constexpr const char * code_Semantic = "#SM_";

	///Token Types   
	static constexpr const char * t_ID = "ID";
	static constexpr const char * t_Int = "INT_NUMBER";
	static constexpr const char * t_Float = "FLOAT_NUMBER";
	static constexpr const char * t_LogConst = "LOGICAL_CONSTANT"; 
	static constexpr const char * t_ReOp = "RELATIONAL_OPERATOR";
	static constexpr const char * t_LogOp = "LOGICAL_OPERATOR";

	/// SymbolCategory Translations
	static constexpr const char * GLO_VAR = "Global Var";
	static constexpr const char * LO_VAR= "Local Var";


	///KeyWords 
	static constexpr const char * k_Func = "function";
	static constexpr const char * k_Var = "var";
	static constexpr const char * k_Main = "main";
	static constexpr const char * k_Return= "Return";


	///  messages 
	static string GlobalScope = "<GLOBAL SCOPE>";

	/// Data Types 
	///Valid Var endings 
	// all the spellings of the keyword that can come after 'Value' 
	static constexpr const char * Value_i = "int";
	static constexpr const char * Value_f = "float";
	static constexpr const char * Value_s = "string";
	static constexpr const char * Value_b = "bool";
	/*! a vector that contains all the correct values a var can be */
	static const std::vector<string> AllVarAfter = { Value_i,Value_f,Value_s,Value_b };
	static const std::vector<string> AllValidFuncTypes = { Value_i,Value_f ,Value_s ,Value_b,"void" };
	static constexpr const char * AllTypes = "'<int>|<float>|<string>|<bool>|<void>'";
	/// Delimiters 
	static constexpr const char * d_LineEnd = ";";
}