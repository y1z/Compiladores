#include "stdafx.h"
#include "Utility.h"
#include "LexIdentifyIID.h"
#include "LexIndentifyOperator.h"
#include "LexSeparators.h"


LexIdentifyIID::LexIdentifyIID()
{}


LexIdentifyIID::~LexIdentifyIID()
{}

bool LexIdentifyIID::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	std::string PossibleID = "";
	while (code[Index] != ' ' && code[Index] != '\0')
	{
		PossibleID += code[Index];
		if (code[Index] == '\0') { break; }
		Index++;
	}

	if (CheckForValidSequence(PossibleID, Index))
	{
		Token tok(PossibleID, Compiler::ID, LineNumber);
		String^ Converted = gcnew String(PossibleID.c_str());
		Console::WriteLine("ID = {0}", Converted);

		Tokens.emplace_back(tok);
		return true;
	}
	else
	{
		CheckForValidSequence(PossibleID, Index);
	}

	return false;
}

void LexIdentifyIID::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{
	LexSeparators *ptr_Separator = new LexSeparators();
	isValidID = ptr_Separator->IsSeparators(code[Index]);
	if (isValidID)
	{
		ptr_Separator->StateAction(code, Index, LineNumber, Tokens, Keywords);
	}

	delete ptr_Separator;
	if (isValidID == false)
	{
		LexIndentifyOperator *ptr_Operator = new LexIndentifyOperator();
		const char copy = code[Index];
		const char* ptr_copy = &copy;

		std::string temp(ptr_copy);

		isValidID = ptr_Operator->CheckOperatorValid(code, Index, temp);

		if (isValidID) { ptr_Operator->StateAction(code, Index, LineNumber, Tokens, Keywords); }

		delete ptr_Operator;
	}

}

bool LexIdentifyIID::CheckForValidSequence(std::string & PossibleIDs, uint32_t &Index)
{
	for (int i = 0; i < PossibleIDs.size(); ++i)
	{
		/*Checks if the string consist of valid chars*/
		if (!IsLetter(PossibleIDs[i]) && !IsNumber(PossibleIDs[i]))
		{
			/*Checks for the '_' char */
			if (!CheckForValidChar(PossibleIDs[i], PossibleIDs, i))
			{
				/*!move back to before an error accrued*/
				Index -= ((PossibleIDs.size() - 1) - i);

				return false;
			}

		}
	}

	return true;
}

bool LexIdentifyIID::CheckForValidChar(char PossiblyValidChar, std::string &PossibleID, uint32_t InternalIndex)
{
	if (PossiblyValidChar == '_' && !(InternalIndex >= PossibleID.size() - 1))
	{
		if (IsLetter(PossibleID[InternalIndex + 1]) || IsNumber(PossibleID[InternalIndex + 1]))
		{
			return true;
		}
	}
	else if (PossiblyValidChar == '_' && InternalIndex >= PossibleID.size() - 1)
	{
		return false;
	}

	return false;
}
