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
			break;
		}
		Buffer += code[Index];
		Index++;
	}

	CheckForEachInvalidChar(Buffer, LineNumber);
	// avoids getting in a station where it call it self hundreds of times
	if (!isRecursive)
	{
		isRecursive = true;
		std::vector<std::string> DividedBuffer = GenerateErrorStrings(Buffer);

		for (int i = 0; i < DividedBuffer.size() - 1; ++i)
		{
			uint32_t FakeIndex = 0;
			ChangeState(DividedBuffer[i].c_str(), FakeIndex, LineNumber, Tokens, Keywords, 0);
		}

		isRecursive = false;
		return true;
	}
	return false;
}

//
void LexInvalidChar::CheckForEachInvalidChar(const std::string & buffer, uint32_t LineNumber)
{
	for (int i = 0; i < buffer.size(); ++i)
	{
		if (!IsLetter(buffer[i]) && !IsNumber(buffer[i]))
		{
			m_InvalidCharAndPositions.emplace_back(std::make_pair(i, buffer[i]));
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

std::vector<std::string> LexInvalidChar::GenerateErrorStrings(const std::string & Buffer)
{
	std::vector < std::string > Result;

	for (std::pair<int, char> Pair : m_InvalidCharAndPositions)
	{
		std::string SeparatedStr = Buffer.substr(0, Pair.first + 1);
		Result.emplace_back(SeparatedStr);
		PrintToConsole("Here is the Separated String {0}", SeparatedStr);
	}
	return Result;
}

std::size_t LexInvalidChar::GetDelta(std::size_t PrevIndex, std::size_t NextIndex)
{
	return NextIndex - PrevIndex;
}

void LexInvalidChar::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{
	ILexerState * ptr_Finder = new LexStateFinder();
	ptr_Finder->m_refErrrorsMod = this->m_refErrrorsMod;
	ptr_Finder->StateAction(code, Index, LineNumber, Tokens, Keywords);

	TrasferToken(this, ptr_Finder);

	delete ptr_Finder;
}