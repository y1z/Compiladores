#include "stdafx.h"
#include "LexSeparators.h"
#include "Utility.h"


LexSeparators::LexSeparators()
{}


LexSeparators::~LexSeparators()
{}

bool LexSeparators::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	while (code[Index] != '\0')
	{
		if (IsSeparators(code[Index]))
		{
			char Character = code[Index];
			std::string Lex (&Character);
		
			Token Generated(Lex, Compiler::SEPARATOR, LineNumber);
			m_GeneratedTokens.emplace_back(Generated);
		}
		else
		{
			break;
		}

		Index++;
	}

	return false;
}

void LexSeparators::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{}

bool LexSeparators::IsSeparators(char PosibleSeparator)
{
	Console::WriteLine("here is the PosibleSeparator {0}", ConvertChar(PosibleSeparator));
	for (char separators : Sparators)
	{
		if (PosibleSeparator == separators)
		{
			Console::WriteLine("Confirmed Separator {0}", ConvertChar(PosibleSeparator));
			return true;
		}
	}
	Console::WriteLine("Confirmed Not Separator {0} ", ConvertChar(PosibleSeparator));
	return false;
}
