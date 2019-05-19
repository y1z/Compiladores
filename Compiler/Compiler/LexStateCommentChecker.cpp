#include "stdafx.h"
#include "LexStateCommentChecker.h"
LexStateCommentChecker::LexStateCommentChecker()
{}

LexStateCommentChecker::~LexStateCommentChecker()
{}

bool LexStateCommentChecker::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* m_Keywords)
{
	// this represent the proper manner to close a comment 
	constexpr const char *ExpetedEnd = "*/";
	// checks for a match in characters
	uint8_t CountCharMach = 0;

	// while we are not at the end of the file 
	while (code[Index] != 0)
	{
		if (code[Index] == ExpetedEnd[0])
		{
			CountCharMach++;
			//Console::ResetColor();
			char copy = code[Index];
			Console::WriteLine("Here is the char ({0}) and color ", System::Convert::ToChar(copy));

		}
		else if (code[Index] == ExpetedEnd[1])
		{
			CountCharMach++;
		}
		else if (CountCharMach == 2)
		{
			return true;
		}
		Index++;// move to next char
	}

	return false;
}

void LexStateCommentChecker::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{}

