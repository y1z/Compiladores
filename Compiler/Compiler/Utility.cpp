#include "stdafx.h"
#include "Utility.h"
#include "Token.h"


wchar_t ConvertChar(char character)
{
	return System::Convert::ToChar(character);
}

std::string GetLine(const char * code, uint32_t IndexCopy)
{
	std::string Line;
	while (code[IndexCopy] != '\0' && code[IndexCopy] != '\r' && code[IndexCopy] != '\n')
	{
		Line += code[IndexCopy];
		IndexCopy++;
		if (code[IndexCopy] == '\0') { break; }
	}

	return Line;
}

bool IsLetter(const char PossibleLetter)
{
	// check for uppercase
	if (PossibleLetter >= 'A' && PossibleLetter <= 'Z')
	{
		return true;
	}
	if (PossibleLetter >= 'a' && PossibleLetter <= 'z')
	{
		return true;
	}

	return false;
}
//! check if a char represent a number 
bool IsNumber(const char PossibleNumber)
{
	if (PossibleNumber >= '0' && PossibleNumber <= '9')
	{
		return true;
	}
	return false;
}
/*! this is here because i was having some issues with Translating the  enum to String*/
const char * TranslateToken(Compiler::Token_Type token_type)
{
	switch (token_type)
	{
	case Compiler::UNDEFINED:
		return "UNDEFINED";
		break;
	case Compiler::ID:
		return "ID";
		break;
	case Compiler::INT_NUMBER:
		return "INT_NUMBER";
		break;
	case Compiler::FLOAT_NUMBER:
		return "FLOAT_NUMBER";
		break;
	case Compiler::STRING_CONSTANT:
		return "STRING_CONSTANT";
		break;
	case Compiler::LOGICAL_CONSTANT:
		return "LOGICAL_CONSTANT";
		break;
	case Compiler::RELATIONAL_OPERATOR:
		return "RELATIONAL_OPERATOR";
		break;
	case Compiler::LOGICAL_OPERATOR:
		return "LOGICAL_OPERATOR";
		break;
	case Compiler::GROUPING_OPERATOR:
		return "GROUPING_OPERATOR";
		break;
	case Compiler::UNARY_LOGICAL_OPERATOR:
		return "UNARY_LOGICAL_OPERATOR";
		break;
	case Compiler::ASSIGN_OPERATOR:
		return "ASSIGN_OPERATOR";
		break;
	case Compiler::ARITHMETIC_OPERATOR:
		return "ARITHMETIC_OPERATOR";
		break;
	case Compiler::DIMENSION_OPERATOR:
		return "DIMENSION_OPERATOR";
		break;
	case Compiler::SEPARATOR:
		return "SEPARATOR";
		break;
	case Compiler::KEYWORD:
		return "KEYWORD";
		break;
	}

	return "ERROR";
}

void IgnoreNewLineChar(const char* code, uint32_t & Index, uint32_t &LineNumber)
{
	LineNumber++;
	const char PossiblyReapeatingChar = code[Index];

	while (code[Index] == '\n' || code[Index] == '\r')
	{
		Index++;
		// in the case there are multiple newlines 
		if (code[Index] == PossiblyReapeatingChar)
		{ LineNumber++; }
	}

}

void PrintToConsole(const std::string & Message)
{
	System::String ^MessageString = gcnew String(Message.c_str());
	Console::WriteLine(" {0} ", MessageString);
}

void PrintToConsole(const char Format[], const std::string & Message)
{
	System::String ^MessageString = gcnew String(Message.c_str());
	System::String ^FormatString = gcnew String(Format);
	Console::WriteLine(FormatString, MessageString);
}

void PrintToConsole(const char Format[], int Count, bool ^Result)
{
	string StrCount = std::to_string(Count);
	System::String ^MessageString = gcnew String(StrCount.c_str());

	System::String ^FormatString = gcnew String(Format);
	if (*Result == true)
	{
		System::String ^AddtionalInfo = " Passed ";
		Console::WriteLine(FormatString, MessageString, AddtionalInfo);
	}
	else
	{
		System::String ^AddtionalInfo = " Did Not Pass ";
		Console::WriteLine(FormatString, MessageString, AddtionalInfo);
	}
}

bool CheckToStopLexAnalisis(msclr::gcroot<Compiler::ErrorsModule^> m_refErrrorsMod)
{
	if (!m_refErrrorsMod->IsMaxErrorReached())
	{
		return true;
	}

	return false;
}

bool IsNumberSequence(const std::string & Str)
{
	for (const char PossibleNum : Str)
	{
		if (!IsNumber(PossibleNum))
		{ return false; }
	}

	return true;
}

bool SkipUntil(Compiler::LexAnalyzer * ptr_lex, const std::string & Delimiter)
{
	// to indicate that we check all the tokens
	bool IsFinish = false;

	while (!IsFinish)
	{
		if (!ptr_lex->GetCurrentToken()->getLex().compare(Delimiter))
		{
			return true;
		}
		// check if we reached the end 
		IsFinish = ptr_lex->AdvanceTokenIndex();
	}

	return false;
}
// TODO : fix positions of the 'if's 
string GetDataTypeFromToken(const Token * ptr_Tok)
{
	if (!ptr_Tok->getLex().compare("int"))
	{
		return string("int");
	}
	if (!ptr_Tok->getLex().compare("float"))
	{
		return string("float");
	}
	if (!ptr_Tok->getLex().compare("string"))
	{
		return string("string");
	}
	if (!ptr_Tok->getLex().compare("bool"))
	{
		return string("bool");
	}
	if (!ptr_Tok->getLex().compare("void"))
	{
		return string("void");
	}

	return string("ERRRRORRRORRROROR");
}

bool MoveLexWithLambda(Compiler::LexAnalyzer * ptr_lex, const string &Delimter, bool(*Pred)(Compiler::LexAnalyzer *lex, const string &Delimiter))
{
	return Pred(ptr_lex, Delimter);
}

bool MoveAndAssignTokenIndex(Compiler::LexAnalyzer * ptr_Lex, const Token *& ptr_token)
{
	if (ptr_Lex->AdvanceTokenIndex())
	{
		ptr_token = ptr_Lex->GetCurrentToken();
		return true;
	}

	return false;
}

bool CompareTokenTypes(const Token * ptr_token, const char * Expected)
{
	string TokenType = TranslateToken(ptr_token->getType());
	if (!TokenType.compare(Expected))
	{
		return true;
	}

	return false;
}

