#include "stdafx.h"
#include "Utility.h"
#include "LexInvalidChar.h"


LexInvalidChar::LexInvalidChar()
{}


LexInvalidChar::~LexInvalidChar()
{}

bool LexInvalidChar::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	std::string Buffer = "";

	while (code[Index] != 0 || code[Index] != '\0')
	{
		if (code[Index] == ' ' || code[Index] == '\0')
		{
			CheckForEachInvalidChar(Buffer,LineNumber);
		}
		Buffer += code[Index];
		Index++;
	}

	return true;
}
/// TODO  ADD ERROR MESSAGE 
void LexInvalidChar::CheckForEachInvalidChar(const std::string & buffer, uint32_t LineNumber)
{
	std::vector<int> InvalidCharPos;

	for (int i = 0; i < buffer.size(); ++i)
	{
		if (IsLetter(buffer[i]) && IsNumber(buffer[i]))
		{
			InvalidCharPos.emplace_back(i);
			if (buffer.size() == 0)
			{
				AddErroMessage(0, i, LineNumber, buffer);

			}

		}
	}
}

void LexInvalidChar::AddErroMessage(int Start, int End, uint32_t LineNumber, const std::string & buffer)
{
	int StringLength = End - Start;

	std::string ErrorDesc = buffer.substr(Start, StringLength);

	m_refErrrorsMod->AddLexError(LineNumber, LEX_INVALID_CHAR, ErrorDesc);
}



void LexInvalidChar::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{}

