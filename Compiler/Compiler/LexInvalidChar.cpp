#include "stdafx.h"
#include "Utility.h"
#include "LexStateFinder.h"
#include "LexSeparators.h"
#include "LexIndentifyOperator.h"
#include "LexInvalidChar.h"


LexInvalidChar::LexInvalidChar()
{}

LexInvalidChar::~LexInvalidChar()
{}

bool LexInvalidChar::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	std::string Buffer = "";
	// recollecting data 
	while (code[Index] != '\0' && code[Index] != '\t' && code[Index] != '\n' && !m_refErrrorsMod->IsMaxErrorReached())
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
		std::vector<std::string> ErrorLines = GenerateErrorStrings(Buffer);
		std::vector<bool> ValidCharIndexes = FindValidChars(Buffer.size());
		// Creates all the related error massages 
		for (std::string Str : ErrorLines)
		{
			if (!AddErroMessage(Str, LineNumber))
			{
				break;
			}
		}

		// get every char that does NOT create an error.
		std::vector<std::string> ValidLines = CheckAllValidChars(ValidCharIndexes, Buffer);
		// find which state does every valid char belong to 
		for (std::string &Str : ValidLines)
		{
			uint32_t FakeIndex = 0;
			ChangeState(Str.c_str(), FakeIndex, LineNumber, Tokens, Keywords, 1);
		}

		isRecursive = false;
		return true;
	}
	return false;
}

//
void LexInvalidChar::CheckForEachInvalidChar(const std::string & buffer, uint32_t LineNumber)
{
	LexSeparators * ptr_Separator = new LexSeparators();
	LexIndentifyOperator *ptr_Operator = new LexIndentifyOperator();


	for (int i = 0; i < buffer.size(); ++i)
	{
		if (!IsLetter(buffer[i]) && !IsNumber(buffer[i])
			&& !ptr_Separator->IsSeparators(buffer[i]) && !ptr_Operator->isOperator(buffer[i]))
		{
			m_InvalidCharAndPositions.emplace_back(std::make_pair(i, buffer[i]));
		}
	}

	delete ptr_Separator;
	delete ptr_Operator;

	isAlreadyChecked = true;
}

bool LexInvalidChar::AddErroMessage(std::string &ErrorLine, uint32_t LineNumber)
{
	ErrorLine += " <=== ";
	return m_refErrrorsMod->AddLexError(LineNumber, LEX_INVALID_CHAR, ErrorLine);
}

std::vector<std::string> LexInvalidChar::CheckAllValidChars(const std::vector<bool> &ValidCharIndexes, const std::string &buffer)
{
	std::vector<std::string> Result;
	// there could be a sequence of char's that's why it's a string  
	std::string ValidChars = "";

	bool isValidChar = false;

	std::size_t Delta = 0;

	for (int i = 0; i < ValidCharIndexes.size(); ++i)
	{
		if (ValidCharIndexes[i] == true)
		{
			ValidChars += buffer[i];
		}
		else
		{
			if (!ValidChars.empty())
			{
				Result.emplace_back(ValidChars);
				ValidChars.clear();
			}

		}
		PrintToConsole(ValidChars);
	}
	// for when the valid char is at the end of the string 
	if (!ValidChars.empty())
	{
		Result.emplace_back(ValidChars);
		ValidChars.clear();
	}

	return Result;
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

std::vector<bool> LexInvalidChar::FindValidChars(std::size_t bufferSize)
{
	/*
	* true = valid char
	* false = invalid char
	*/
	// assume that all char are valid by default
	std::vector<bool> ValidAndInvalid(bufferSize, true);

	for (auto Pair : m_InvalidCharAndPositions)
	{
		ValidAndInvalid[Pair.first] = false;
	}

	return ValidAndInvalid;
}

void LexInvalidChar::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{
	ILexerState * ptr_Finder = new LexStateFinder();
	ptr_Finder->m_refErrrorsMod = this->m_refErrrorsMod;

	ptr_Finder->StateAction(code, Index, LineNumber, Tokens, Keywords);

	delete ptr_Finder;
}