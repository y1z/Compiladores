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
	if (!m_refErrrorsMod->IsMaxErrorReached())
	{

		while (code[Index] != '\0' && code[Index] != ' ')
		{
			if (code[Index] == '\r' || code[Index] == '\n')
			{
				break;
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

		if (isFloat)
		{
			if (CheckForValidFloat(Numbuffer, LineNumber, Index))
			{
				Token tok(Numbuffer, Compiler::FLOAT_NUMBER, LineNumber);

				PrintToConsole(" Here is a float : [{0}] ", Numbuffer);
				Tokens.emplace_back(tok);
				return true;
			}
			else
			{
				PrintToConsole("Here is a Invalid Number : [{0}] ", Numbuffer);
				std::string ErrorMessage(INVALID_FLOAT);
				ErrorMessage += "needs Digit after point\t";
				Numbuffer += " <--";
				if (this->m_refErrrorsMod->AddLexError(LineNumber, ErrorMessage.c_str(), Numbuffer))
				{
					return false;
				}
				return false;
			}
		}
		else
		{
			Token tok(Numbuffer, Compiler::INT_NUMBER, LineNumber);
			PrintToConsole(" Here is a int : [{0}] ", Numbuffer);
			Tokens.emplace_back(tok);
			return true;
		}
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
bool LexStateNumber::CheckForValidFloat(std::string & PossibleFloat, uint32_t LineNumber, uint32_t &Index)
{
	bool isValidFloat = true;
	uint8_t PointFoundCount = 0;
	std::size_t StrIndex = 0;
	// if the numbers something like .3 it's find ,3.3 is also find ,3. that an error 
	for (char digit : PossibleFloat)
	{
		if (PointFoundCount > 1)
		{
			// this is because 3..3 the first half is invalid, the other half is valid 
			Index += (StrIndex - (PossibleFloat.size() + 1));
			uint32_t CopyIndex = Index;
			// only generate an error where the error resides 
			PossibleFloat = PossibleFloat.substr(0, (PossibleFloat.size() - StrIndex) + 1);
			PrintToConsole("Resulting Float {0}", PossibleFloat);

			if (CheckForValidFloat(PossibleFloat, LineNumber, CopyIndex))
			{
				return true;
			}

			return false;
		}

		else	if (!IsNumber(digit))
		{
			isValidFloat = false;
			PointFoundCount++;
		}

		else
		{
			isValidFloat = true;
		}
		StrIndex++;
	}

	return isValidFloat;
}
