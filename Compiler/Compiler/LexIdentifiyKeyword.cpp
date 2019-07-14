#include "stdafx.h"
#include "LexStateFinder.h"
#include "LexScannig.h"
#include "LexIdentifiyKeyword.h"
#include "LexStateNumber.h"
#include "Utility.h"


LexIdentifiyKeyword::LexIdentifiyKeyword()
{}


LexIdentifiyKeyword::~LexIdentifiyKeyword()
{}

bool LexIdentifiyKeyword::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	std::string PossibleKeyword = "";
	/* get the possible keyword*/
	while (code[Index] != ' ' && code[Index] != '\0' && !m_refErrrorsMod->IsMaxErrorReached())
	{
		if (IsLetter(code[Index]) || code[Index] == '_' || IsNumber(code[Index]))
		{
			PossibleKeyword += code[Index];
		}
		else
		{
			break;
		}

		if (code[Index] == 0) { break; }
		Index++;
	}
	// check if the string is a keyword
	auto Match = Keywords->find(PossibleKeyword);

	// check if in the keyword map 
	if (Match != Keywords->end())
	{
		if (!CheckKeywordExecptions(PossibleKeyword, LineNumber,Tokens))
		{
			Token tok(PossibleKeyword, Compiler::KEYWORD, LineNumber);
			String^  ConvertedKeyword = gcnew String(PossibleKeyword.c_str());
			Console::WriteLine("KeyWord is : {0} ", ConvertedKeyword);

			Tokens.emplace_back(tok);
			return true;
		}
		else
		{
			Token tok(PossibleKeyword, Compiler::LOGICAL_CONSTANT, LineNumber);
			String^  ConvertedLogicalConstant = gcnew String(PossibleKeyword.c_str());
			Console::WriteLine("KeyWord is : {0} ", ConvertedLogicalConstant);
			Tokens.emplace_back(tok);
			return true;
		}

	}
	else	// confirmed that's not a keyword or logical constant
	{
		Index -= PossibleKeyword.size();
	}

	return false;
}

bool LexIdentifiyKeyword::CheckKeywordExecptions(std::string &Keyword, uint32_t LineNumber, std::vector<Token> &Tokens)
{
	if (Keyword == "true" || Keyword == "false")
	{
		return true;
	}

	return false;
}

void LexIdentifiyKeyword::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{}
