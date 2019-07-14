#pragma once
// regular includes 
#include <cinttypes>
#include <string>
#include <vector>
#include <cmath>
#include <map>
using std::string;
// MY includes 
#include "Utility.h"
//

namespace Compiler {
	/*! this is used to determinate which
	value, function the node will hold */
	enum class SymbolCategory
	{
		unknown,
		global_var,
		local_var,
		param,
		function
	};

};