#include "stdafx.h"
#include "LexStateCommentChecker.h"
LexStateCommentChecker::LexStateCommentChecker()
{}

LexStateCommentChecker::~LexStateCommentChecker()
{}

bool LexStateCommentChecker::StateAcction(const char * code, uint32_t &Index, std::vector<Token>& Tokens)
{
	// this  represent the proper manner to close a comment 
	constexpr const char *ExpetedEnd = "*/";
	// checks for a match in characters
	uint8_t CountCharMach = 0;

	// while we are not at the end of the file 
	while (code[Index] != 0)
	{
		if (code[Index] == ExpetedEnd[0])
		{
			CountCharMach++;
		}
		else if (code[Index] == ExpetedEnd[1])
		{
			CountCharMach++;
		}
		else if(CountCharMach == 4)
		{
			return true;
		}
		Index++;// move to next char
	}


	return true;
}
