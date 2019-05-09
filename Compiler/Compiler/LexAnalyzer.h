#pragma once
#include "Usable_Windows.h"
#include "ErrorsModule.h"
#include <vcclr.h>


namespace Compiler {
	public class LexAnalyzer
	{
	public:
		LexAnalyzer(ErrorsModule ^Err);
		~LexAnalyzer();

		bool ParseSourceCode(const char *stc);
	};

}


