#include "stdafx.h"
#include "ErrorFunctions.h"
#include "GlobolNames.h"
#include "SynStateFunction.h"
#include "SynStateParam.h"
#include "SynStateVar.h"

Compiler::SynStateFunction::SynStateFunction(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic)
	:ISynState(ptr_Lex, ptr_Syn, ptr_PrevState, mptr_SymbolsTable, mptr_Semantic)
{}

Compiler::SynStateFunction::~SynStateFunction()
{}
//! already found the key word "function"
bool Compiler::SynStateFunction::CheckSyntax()
{
	bool Continue = mptr_Lex->AdvanceTokenIndex();
	// check for id and parenthesis
	string ExpectedSequence = { "i()" };
	// too keep track of which char I'm using in 'ExpectedSequence'
	int8_t SequencePos = 0;

	// check param/param's
	while (Continue && SequencePos < ExpectedSequence.size())
	{
		ReadOnlyToken Tok = mptr_Lex->GetCurrentToken();
		string TokenType = TranslateToken(Tok->getType());

		switch (ExpectedSequence[SequencePos])
		{
			// check ID 
		case('i'):
			if (!TokenType.compare(g_Names::t_ID))
			{
				m_FunctionName = Tok->getLex();
			}
			else
			{
				string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(g_Names::t_ID, TokenType.c_str());
				mptr_Lex->m_refErrrorsMod->AddSynError(Tok->getLineNum(), ErrorDesc, "");
				return false;
			}
			break;
			// make sure the param's syntax is correct
		case('('):
			if (!Tok->getLex().compare("("))
			{
				ISynState* ParamState = new SynStateParam(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic);

				Continue = ParamState->CheckSyntax();
				delete ParamState;
			}
			else
			{
				string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(&ExpectedSequence[SequencePos], Tok->getLex().c_str());
				mptr_Lex->m_refErrrorsMod->AddSynError(Tok->getLineNum(), ErrorDesc, "");
				return false;
			}
			break;

		case(')'):
			if (!Tok->getLex().compare(")"))
			{
				isValid = true;
			}
			else
			{
				string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(&ExpectedSequence[SequencePos], Tok->getLex().c_str());
				mptr_Lex->m_refErrrorsMod->AddSynError(Tok->getLineNum(), ErrorDesc, "");
				return false;
			}
			break;
		};

		SequencePos++;
		Continue = mptr_Lex->AdvanceTokenIndex();
	}

	if (Continue)
	{
		isValid = CheckFunctionType();
	}

	return isValid;
}

bool Compiler::SynStateFunction::CheckFunctionType()
{
	ReadOnlyToken token = mptr_Lex->GetCurrentToken();
	bool IsTypeValid = false;

	if (!token->getLex().compare(":"))
	{
		// make sure we can move forward
		isValid = MoveAndAssignTokenIndex(mptr_Lex, token);
		if (isValid)
		{
			// checking for type void 
			if (!token->getLex().compare("void"))
			{ IsTypeValid = true; }
			// checking for the rest of the types
			for (string ValidTypes : g_Names::AllVarAfter)
			{
				if (!token->getLex().compare(ValidTypes))
				{
					IsTypeValid = true;
				}
			}
		}
		else
		{
			string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(":", token->getLex().c_str());
			mptr_Lex->m_refErrrorsMod->AddSynError(token->getLineNum(), ErrorDesc, "");
		}

	}

	if (IsTypeValid)
	{
		return CheckFunctionBlock();
	}


	return false;
}

bool Compiler::SynStateFunction::CheckFunctionBlock()
{
	isInFunctionBlock = true;
	ReadOnlyToken token = nullptr;

	isInFunctionBlock = MoveAndAssignTokenIndex(mptr_Lex, token);
	if (!token->getLex().compare("{"))
	{
		while (isInFunctionBlock)
		{



		}
	}
	return false;
}
