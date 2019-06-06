#include "stdafx.h"
#include "Utility.h"
#include "LexStateFinder.h"
#include "LexInvalidChar.h"


LexInvalidChar::LexInvalidChar()
{}


LexInvalidChar::~LexInvalidChar()
{}

bool LexInvalidChar::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	std::string Buffer = "";
	// recollecting data 
	while (code[Index] != 0 || code[Index] != '\0')
	{
		if (code[Index] == ' ' || code[Index] == '\0')
		{
			CheckForEachInvalidChar(Buffer, LineNumber);
			break;
		}
		Buffer += code[Index];
		Index++;
	}
	// avoids getting in a station where it call it self hundreds of times
	if (!isRecursive)
	{
		isRecursive = true;


		isRecursive = false;
	}


	return false;
}

/// TODO  ADD ERROR MESSAGE 
void LexInvalidChar::CheckForEachInvalidChar(const std::string & buffer, uint32_t LineNumber)
{
	bool isFirstPoint = true;
	int PrevPoint = 0;
	for (int i = 0; i < buffer.size(); ++i)
	{
		if (!IsLetter(buffer[i]) && !IsNumber(buffer[i]))
		{
			m_InvalidCharPos.emplace_back(i);
			if (isFirstPoint)
			{
				PrevPoint = i;
				AddErroMessage(0, i, LineNumber, buffer);
				isFirstPoint = false;
				m_InvalidCharPos.emplace_back(i);
			}
			else
			{
				AddErroMessage(PrevPoint + 1, i, LineNumber, buffer);
				PrevPoint = i;
			}
		}
	}

	isAlreadyChecked = true;
}

void LexInvalidChar::AddErroMessage(int Start, int End, uint32_t LineNumber, const std::string & buffer)
{
	int StringLength = End - Start;

	std::string ErrorDesc = buffer.substr(Start, StringLength);

	m_refErrrorsMod->AddLexError(LineNumber, LEX_INVALID_CHAR, ErrorDesc);
}

std::vector<std::string> LexInvalidChar::DivideBuffer(const std::string & Buffer)
{
	std::vector < std::string > Result;
	Result[0] = "";
	std::size_t Delta = 0;
	for (int i = 0; i < m_InvalidCharPos.size() - 1; ++i)
	{
		Delta = GetDelta(m_InvalidCharPos[i], m_InvalidCharPos[i + 1]);

		int InvalidCharPos = m_InvalidCharPos[i];
		if (Delta == 1)
		{
			Result[Result.size() - 1] += Buffer[InvalidCharPos];
		}
		else
		{
			std::string AddedString;
			AddedString += Buffer[InvalidCharPos];
			Result.emplace_back(AddedString);
		}

	}

	return Result;
}

std::size_t LexInvalidChar::GetDelta(std::size_t PrevIndex, std::size_t NextIndex)
{
	std::size_t Delta = NextIndex - PrevIndex;

	return Delta;
}

void LexInvalidChar::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{
	ILexerState * ptr_Finder = new LexStateFinder();
	ptr_Finder->m_refErrrorsMod = this->m_refErrrorsMod;
	//	ptr_Finder->StateAction(code,Index, LineNumber)

	delete ptr_Finder;
}