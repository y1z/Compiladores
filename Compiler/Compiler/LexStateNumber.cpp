#include "stdafx.h"
#include "LexStateNumber.h"
#include "Utility.h"

LexStateNumber::LexStateNumber()
{}


LexStateNumber::~LexStateNumber()
{}

bool LexStateNumber::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	std::string Numbuffer = "";
	while (code[Index] != '\0' && code[Index] != ' ')
	{
		if (code[Index] == '\r')
		{
			LineNumber++;
		}
		/*check for char related to int and floats*/
		if (!IsNumber(code[Index]))
		{
			if (!CheckForPoint(code[Index]))
			{
				break;
			}
		}
		Numbuffer += code[Index];

		if (code[Index] == '\0') { break; }
		Index++;
	}

	String^ temp = gcnew String(Numbuffer.c_str());
	Console::WriteLine(" Here is the NUMber : [{0}] ", temp);

	if (isFloat)
	{
		if (CheckForValidFloat(Numbuffer, LineNumber))
		{
			Token tok(Numbuffer, Compiler::FLOAT_NUMBER, LineNumber);
			Tokens.emplace_back(tok);
			return true;
		}
		else
		{
			this->m_refErrrorsMod->AddLexError(LineNumber, INVALID_FLOAT, Numbuffer);
			return false;
		}
	}
	else
	{
		Token tok(Numbuffer, Compiler::INT_NUMBER, LineNumber);
		m_GeneratedTokens.emplace_back(tok);
		return true;
	}
	return false;
}

void LexStateNumber::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{}

bool LexStateNumber::CheckForPoint(const char PossiblePoint)
{
	if (PossiblePoint == '.')
	{
		isFloat = true;
		return true;
	}

	return false;
}
// checks for 2.2 and not 2. 
bool LexStateNumber::CheckForValidFloat(std::string & PossibleFloat, uint32_t LineNumber)
{
	bool isValidFloat = true;
	uint8_t PointFoundCount = 0;
	// if the numbers something like .3 it's find ,3.3 is also find ,3. that an error 
	for (char digit : PossibleFloat)
	{

		if (!IsNumber(digit))
		{
			isValidFloat = false;
			PointFoundCount++;
		}
		if (PointFoundCount > 1)
		{
			return false;
		}
		else
		{
			isValidFloat = true;
		}
	}

	return isValidFloat;
}
