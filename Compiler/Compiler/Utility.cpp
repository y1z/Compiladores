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

