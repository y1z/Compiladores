#include "stdafx.h"
#include "LexStringChecker.h"
#include "Utility.h"
#include <string>

LexStringChecker::LexStringChecker()
{}


LexStringChecker::~LexStringChecker()
{}

bool LexStringChecker::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	uint32_t CopyIndex = Index;

	// use to know if use closed the string properly
	int8_t DoubleQuoteCount = 0;

	std::string Lexema = "";
	while (code[Index] != '\0' && !m_refErrrorsMod->IsMaxErrorReached())
	{

		if (code[Index] == '\"')
		{
			DoubleQuoteCount++;
		}
		if (code[Index] == '\n' || code[Index] == '\r')
		{
			PrintToConsole("Error new line in String {0} ", Lexema);

			ReportError(LineNumber, code, CopyIndex);
			DoubleQuoteCount = 0;
			IgnoreNewLineChar(code, Index, LineNumber);
			return false;
		}
		if (DoubleQuoteCount == 2)
		{
			Lexema += code[Index];
			PrintToConsole("Here is a String constant {0}", Lexema);
			// so it does NOT reevaluate the char " twice 
			Index++;

			Tokens.emplace_back(Token(Lexema, Compiler::STRING_CONSTANT, LineNumber));

			return true;
		}
		if (code[Index] == '\0')
		{
			ReportError(LineNumber, code, CopyIndex);
			Index++;
			return false;
		}
		Lexema += code[Index];

		Index++;
	}
	PrintToConsole("Here String that's not closed {0} ", Lexema);
	// for when we reach the end of the code 
	ReportError(LineNumber, code, CopyIndex);

	return true;
}

void LexStringChecker::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{}

bool LexStringChecker::ReportError(uint32_t LineNumber, const char * code, uint32_t Index, const char *CustomMessage)
{
	if (CustomMessage == nullptr)
	{
		std::string ErrorLine = GetLine(code, Index);
		return m_refErrrorsMod->AddLexError(LineNumber, STRING_NOT_CLOSED, ErrorLine);
	}
	else
	{
		std::string ErrorLine = GetLine(code, Index);
		System::String ^Converted = gcnew String(ErrorLine.c_str());
		return 	m_refErrrorsMod->AddLexError(LineNumber, CustomMessage, ErrorLine);
	}

}
