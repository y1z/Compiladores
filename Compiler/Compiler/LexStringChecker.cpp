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
	uint32_t CopyLineNumber = LineNumber;
	// use to know if use closed the string properly
	int8_t DoubleQuoteCount = 0;

	std::string Lexema = "";
	while (code[Index] != '\0')
	{

		String ^ Converted = gcnew String(Lexema.c_str());
		Console::WriteLine(" String constant {0} ", Converted);
		if (code[Index] == '\"')
		{
			DoubleQuoteCount++;
		}
		if (code[Index] == '\n' || code[Index] == '\r')
		{
			GetLine(code, CopyIndex);
			ReportError(LineNumber, code, Index);
			CopyIndex = Index;
			DoubleQuoteCount = 0;
			IgnoreSpaceChars(code, Index, LineNumber);
			Lexema.clear();
		}
		if (DoubleQuoteCount == 2)
		{
			Lexema += code[Index];

			Tokens.emplace_back(Token(Lexema, Compiler::STRING_CONSTANT, LineNumber));

			return true;
		}
		if (code[Index] == '\0')
		{
			ReportError(CopyLineNumber, code, Index);
		}
		Lexema += code[Index];

		Index++;
	}

	return true;
}

void LexStringChecker::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{}

void LexStringChecker::ReportError(uint32_t LineNumber, const char * code, uint32_t Index, const char *CustomMessage)
{
	if (CustomMessage == nullptr)
	{
		std::string ErrorLine = GetLine(code, Index);
		m_refErrrorsMod->AddLexError(LineNumber, STRING_NOT_CLOSED, ErrorLine);
	}
	else
	{
		std::string ErrorLine = GetLine(code, Index);
		System::String ^Converted = gcnew String(ErrorLine.c_str());
		m_refErrrorsMod->AddLexError(LineNumber, CustomMessage, ErrorLine);
	}

}
