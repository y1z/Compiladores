#include "stdafx.h"
#include "LexIdentifiyKeyword.h"


LexIdentifiyKeyword::LexIdentifiyKeyword()
{}


LexIdentifiyKeyword::~LexIdentifiyKeyword()
{}

bool LexIdentifiyKeyword::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	std::string PosibleKeyword = "";
	while (code[Index] != ' ' && code[Index] != '\0')
	{
		PosibleKeyword += code[Index];

		if (code[Index] == 0) { break; }
		Index++;
	}

	auto Match = Keywords->find(PosibleKeyword);

	if (Match != Keywords->end())
	{
		if (!CheckKeywordExecptions(PosibleKeyword, LineNumber))
		{
			Token tok(PosibleKeyword, Compiler::KEYWORD, LineNumber);
			String^  ConvertedKeyword = gcnew String(PosibleKeyword.c_str());
			Console::WriteLine("KeyWord is : {0} ", ConvertedKeyword);
			m_GeneratedTokens.emplace_back(tok);
			return true;
		}
	}

	return false;
}

bool LexIdentifiyKeyword::CheckKeywordExecptions(std::string &Keyword, uint32_t LineNumber)
{
	if (Keyword == "true" || Keyword == "false")
	{
		Token tok(Keyword, Compiler::LOGICAL_CONSTANT, LineNumber);
		String^  ConvertedKeyword = gcnew String(Keyword.c_str());
		Console::WriteLine("KeyWord is : {0} ", ConvertedKeyword);
		m_GeneratedTokens.emplace_back(tok);
		return true;
	}

	return false;
}

void LexIdentifiyKeyword::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{}
