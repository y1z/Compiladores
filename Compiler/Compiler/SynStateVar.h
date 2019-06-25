#pragma once
#include "stdafx.h"
#include "ISynState.h"
/*!
\brief takes care of registering the var's and making sure they are 
of a valid type aka anything but 'void' */

namespace Compiler {

	class SynStateVar : public ISynState
	{
	public: 
		SynStateVar(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos);
		~SynStateVar();
	public: // functions 
		bool CheckSyntax() override;
		uint32_t FindDimension();
	private:
		//! this is for keeping track of the terminal of the var and it's dimension
		std::vector<std::map<std::string, int>> m_VarsList;
		//! this is used to read all input from the tokens 
		ReadOnlyToken mptr_Token = nullptr;
	};

}