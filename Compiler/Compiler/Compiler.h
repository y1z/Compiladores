#pragma once
#include"Usable_Windows.h"
#include "LexAnalyzer.h"
#include "ErrorsModule.h"
using namespace System;

namespace Compiler {
	// ref significa que sera una clase manejada (se limpia la memoria por me) 
	public ref class Manager
	{
	private:
		void LexAnalysis(String ^srcCode);

	public:
		Manager();
		~Manager();

		ErrorsModule ^ptr_Error;
		LexAnalyzer *ptr_Lex = nullptr;

		cli::array<String^ > ^compileProgram(String^ srcCode);

		// TODO: Add your methods for this class here.
	};

};
