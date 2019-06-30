#include "stdafx.h"
#include "ErrorFunctions.h"
#include "GlobolNames.h"
#include "SynStateFunction.h"
#include "SynStateParam.h"
#include "SynStateVar.h"

Compiler::SynStateFunction::SynStateFunction(LexAnalyzer *ptr_Lex, SyntaxAnalysis *ptr_Syn, ISynState *ptr_PrevState, SymbolsTable *ptr_Symblos, SemanticAnalysis *ptr_Semantic)
	:ISynState(ptr_Lex, ptr_Syn, ptr_PrevState, ptr_Symblos, ptr_Semantic)
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
			if (!TokenType.compare(g_Names::t_ID) || !Tok->getLex().compare("main"))
			{
				m_FunctionName = Tok->getLex();
				m_NodeArgs.SetSymbol(m_FunctionName.c_str());
				m_NodeArgs.SetDimension(0);
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
				SynStateParam* ParamState = new SynStateParam(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName);

				Continue = ParamState->CheckSyntax();
				m_ParamNodes = ParamState->GetNodes();
				m_ParamType = ParamState->m_Type;

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
				// making sure to register the params 
				for (auto &Node : m_ParamNodes)
				{
					mptr_SymbolsTable->AddSymbol(Node.GetSymbol(), Node.GetLineNum(), SymbolCategory::param, m_FunctionName, m_ParamType, Node.GetLineNum());
				}
				// Making the Error
				string ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM(&ExpectedSequence[SequencePos], Tok->getLex().c_str());
				mptr_Lex->m_refErrrorsMod->AddSynError(Tok->getLineNum(), ErrorDesc, "");
				return false;
			}
			break;
		};

		SequencePos++;
		Continue = mptr_Lex->AdvanceTokenIndex();
	}

	//! main doe not have a type 
	if (Continue && m_NodeArgs.GetSymblo().compare("main"))
	{
		isValid = CheckFunctionType();
	}
	else if (Continue && !m_NodeArgs.GetSymblo().compare("main"))
	{
		CheckFunctionBlock();
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
			{
				IsTypeValid = true;
				m_NodeArgs.SetType("void");
			}
			// checking for the rest of the types
			for (string ValidTypes : g_Names::AllVarAfter)
			{
				if (!token->getLex().compare(ValidTypes))
				{
					IsTypeValid = true;
					m_NodeArgs.SetType(ValidTypes.c_str());
					//add the symbol
					mptr_SymbolsTable->AddSymbol(m_NodeArgs.GetSymblo(), m_NodeArgs.GetDimension(),
						SymbolCategory::function, g_Names::GlobalScope,
						m_NodeArgs.GetType(), m_NodeArgs.GetLineNum());

					break;
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
		// making sure to register the params 
		for (auto &Node : m_ParamNodes)
		{
			mptr_SymbolsTable->AddSymbol(Node.GetSymbol(), Node.GetLineNum(), SymbolCategory::param, m_FunctionName, m_ParamType, Node.GetLineNum());
		}

		return CheckFunctionBlock();
	}


	return false;
}

bool Compiler::SynStateFunction::CheckFunctionBlock()
{
	isInFunctionBlock = true;
	bool EndOfFunctionBlock = false;
	ReadOnlyToken token = nullptr;
	if (m_FunctionName.compare("main"))
	{
		isInFunctionBlock = MoveAndAssignTokenIndex(mptr_Lex, token);
	}
	token = mptr_Lex->GetCurrentToken();

	if (!token->getLex().compare("{"))
	{
		isInFunctionBlock = MoveAndAssignTokenIndex(mptr_Lex, token);
		while (isInFunctionBlock && !EndOfFunctionBlock)
		{
			if (!token->getLex().compare("var"))
			{
				ISynState *ptr_VarState = new SynStateVar(mptr_Lex, mptr_Syn, this, mptr_SymbolsTable, mptr_Semantic, this->m_FunctionName);
				ptr_VarState->m_CategorySym = SymbolCategory::local_var;
				ptr_VarState->CheckSyntax();
				delete ptr_VarState;
			}
			/// TODO FINSH THIS 
			else	if (!token->getLex().compare("return"))
			{
				MoveAndAssignTokenIndex(mptr_Lex, token);
				if (CompareTokenTypes(token, "INT_NUMBER") || CompareTokenTypes(token, "FLOAT_NUMBER") || CompareTokenTypes(token, "LOGICAL_CONSTANT"))
				{
					MoveAndAssignTokenIndex(mptr_Lex, token);
					if (!token->getLex().compare(g_Names::d_LineEnd))
					{
						MoveAndAssignTokenIndex(mptr_Lex, token);
					}

				}

			}
			if (!token->getLex().compare("}"))
			{
				EndOfFunctionBlock = true;

				MoveAndAssignTokenIndex(mptr_Lex, token);
				return true;
			}


			isInFunctionBlock = MoveAndAssignTokenIndex(mptr_Lex, token);
		}

	}
	else
	{
		string  ErrorDesc = ErrorFuncs::SYN_UNEXPECTED_SYM("{", token->getLex().c_str());
		mptr_Lex->m_refErrrorsMod->AddSynError(token->getLineNum(), ErrorDesc, "");
		return false;
	}

	return false;
}

string Compiler::SynStateFunction::GetFunctionName() const
{
	return this->m_FunctionName;
}
