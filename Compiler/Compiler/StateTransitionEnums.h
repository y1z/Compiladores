#pragma once
#include "stdafx.h"


namespace Compiler {
	/*! this is used in all transitions in the syntax phase of the compiler 
	 * The Number Zero indicate an error
	 *  A Positive non zero number indicate's a string comparison
	 *  A negative Non zero number indicate's a Type Comparison
	 */


	enum class SynStateTransition : int8_t
	{
		ID = -1,//!< need to do type comparison to find out if it's an id 
		Unknown = 0,//!< Error did not find a match 
		Main = 1,
		Var,
		If,
		Else,
		Print,
		Read,
		Function,
		Return,
		FunctionBlock,
		FunctionBlockEnd,
		While,
		For,
		Assign,
		Increament,
		Decrement

	};


	//! to find-out when i should use a string comparison
	static bool shouldUseStringComparasion(SynStateTransition transition)
	{
		if (transition > SynStateTransition::Unknown)
		{
			return true;
		}
		return false;
	}

};