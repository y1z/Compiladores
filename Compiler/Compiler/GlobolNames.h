#pragma once
#include "stdafx.h"
/*!
This file exist so i don't miss spell anything
*/
namespace g_Names {

	///Token names  
	constexpr char * t_ID = "ID";

	///Valid Var endings 
	// all the spellings of the keyword that can come after 'var' 
	constexpr char * Var_I = "int";
	constexpr char * Var_f = "float";
	constexpr char * Var_s = "string";
	constexpr char * Var_b = "bool";
	/*! a vector that contains all the possible spelling's  */
	std::vector<string> AllVarAfter = { Var_I,Var_f,Var_s,Var_b };
}