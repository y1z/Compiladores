#pragma once
#include <vcclr.h>
#include <cinttypes>
#include <string>
#include "LexAnalyzer.h"
#include "SyntaxAnalysis.h"

class SyntaxAnalysis;
class LexAnalyzer;
/*!
\brief this is the interface for each state of the
Syntactic analysis Fazes for the compiler */
namespace Compiler {

	public class ISyntaxState
	{
	public:
		ISyntaxState();

		virtual ~ISyntaxState();

	public:
		/*! this function exist because the constructor was giving me trouble, just treat it like one */
		void InitSyntaxState(LexAnalyzer *ptr_Lex,SyntaxAnalysis *ptr_Syn,ISyntaxState*ptr_Parent);

		virtual bool CheckSyntax() = 0;
	protected:
		//! where we get the tokens from 
		LexAnalyzer* mptr_Lex = nullptr;

		SyntaxAnalysis* mptr_Syn = nullptr;

		//! this is for debugging 
		std::string m_stateName;
		//! or previous
		ISyntaxState *mptr_Parent = nullptr;
	};

}