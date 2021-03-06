#include "stdafx.h"
#include "ErrorsModule.h"
#include "LexStateCommentChecker.h"
#include "Utility.h"
LexStateCommentChecker::LexStateCommentChecker()
{}

LexStateCommentChecker::~LexStateCommentChecker()
{}

bool LexStateCommentChecker::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* m_Keywords)
{
	// checks for a match in characters
	uint32_t CopyIndex = Index;
	uint32_t CopyLine = LineNumber;

	Index++;
	// while we are not at the end of the file 
	while (code[Index] != 0)
	{
		// check for this --> /*  */ not this --> /*/
		if (code[Index] == '*' && code[Index - 1] != '/')
		{
			Console::WriteLine("Current Char {0}", System::Convert::ToChar(code[Index]));
			if (code[Index + 1] == '/')
			{
				Index += 2;
				return true;
			}
			else { Index++; }
		}
		else if (code[Index] == '\r' || code[Index] == '\n')
		{
			IgnoreNewLineChar(code, Index, LineNumber);
		}
		else
		{
			Index++;// move to next char
		}

	}
	/*For the case the comment is located at the end of the file*/

	std::string ErrorLine;
	while ( code[CopyIndex] != 0 || code[CopyIndex] != '\r')
	{
		ErrorLine += code[CopyIndex];
		CopyIndex++;
		if (code[CopyIndex] == 0) { break; }
	}

	m_refErrrorsMod->AddLexError(CopyLine, COMMENT_NOT_CLOSED, ErrorLine);
	return false;
}

void LexStateCommentChecker::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{}

