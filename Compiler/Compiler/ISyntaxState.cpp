#include "stdafx.h"
#include "ISyntaxState.h"
#include "LexAnalyzer.h"
#include "SyntaxAnalysis.h"

namespace Compiler {
	ISyntaxState::ISyntaxState()
	{
	
	}

	ISyntaxState::~ISyntaxState()
	{}

	void ISyntaxState::InitSyntaxState(LexAnalyzer * ptr_L, SyntaxAnalysis * ptr_S, ISyntaxState*ptr_Parent)
	{
		this->mptr_Lex = ptr_L;
		this->mptr_Syn = ptr_S;
		this->mptr_Parent = ptr_Parent;
	}


}