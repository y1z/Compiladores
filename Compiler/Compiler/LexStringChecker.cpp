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
	while (true)
	{
		if (code[Index] == '\"')
		{
			DoubleQuoteCount++;
		}
		if (code[Index] == '\n' || code[Index] == '\r')
		{
			GetErrorLine(code, CopyIndex);
			ReportError(LineNumber, code, Index, "Invalid use of newline in string");
		}
		if (DoubleQuoteCount == 2)
		{
			Lexema += code[Index];
			String^ Temp = gcnew String(Lexema.c_str());
			Console::WriteLine("Here is  the lexema for string constant : {0} ", Temp);

			m_GeneratedTokens.emplace_back(Token(Lexema, Compiler::STRING_CONSTANT, LineNumber));

			return true;
		}
		else if (code[Index] == '\0')
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
		std::string ErrorLine = GetErrorLine(code, Index);
		m_refErrrorsMod->AddLexError(LineNumber, COMMENT_NOT_CLOSED, ErrorLine);
	}
	else
	{
		std::string ErrorLine = GetErrorLine(code, Index);
		System::String ^Converted = gcnew String(ErrorLine.c_str());
		m_refErrrorsMod->AddLexError(LineNumber, CustomMessage, ErrorLine);
	}

}
