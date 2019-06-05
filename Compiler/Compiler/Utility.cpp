#include"stdafx.h"
#include <string>
#include "Utility.h"

wchar_t ConvertChar(char character)
{
	return System::Convert::ToChar(character);
}

std::string GetErrorLine(const char * code, uint32_t IndexCopy)
{
	std::string ErrorLine;
	while (code[IndexCopy] != '\0' || code[IndexCopy] != '\r\n')
	{
		ErrorLine += code[IndexCopy];
		IndexCopy++;
		if (code[IndexCopy] == '\0') { break; }
	}

	return ErrorLine;
}

void TrasferToken(ILexerState * Reciver, ILexerState * Giver)
{
	for (Token tok : Giver->m_GeneratedTokens)
	{
		Reciver->m_GeneratedTokens.emplace_back(tok);
	}
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

bool IsNumber(const char PossibleNumber)
{
	if (PossibleNumber >= '0' && PossibleNumber <= '9')
	{
		return true;
	}
	return false;
}
/*! this exits because i was haven some issues with Traslating the string */
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

	return "UNDEFINED";
}


