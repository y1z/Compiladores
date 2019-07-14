#include "stdafx.h"
#include "Utility.h"
#include <array>
#include "LexIndentifyOperator.h"


LexIndentifyOperator::LexIndentifyOperator()
{}


LexIndentifyOperator::~LexIndentifyOperator()
{}

bool LexIndentifyOperator::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords)
{
	/*
	char = the operator
	int = Methods used the check operator (it could have a = to it right )
	0 = check for equals sign
	1 = check for repeat
	2 = alone
	*/
	//static std::map<char, int> Operators = { {'<',0},{'>',0},{'!',0},{'=',0},
	//{'|',1}, {'&',1} ,{'[',2} ,{']',2} ,
	//{'+',2} ,{'-',2},{'*',2},{'%',2},{'/',2} ,{'^',2} ,
	//{'{',2},{'}',2} , {'(',2} , {')',2} };


	auto Result = Operators.find(code[Index]);
	if (!m_refErrrorsMod->IsMaxErrorReached())
	{
		if (Operators.end() != Result)
		{
			std::string Operator;
			// creates Relational operators
		//	std::string CountOfError;
			PrintToConsole("Error Count {0} ", m_refErrrorsMod->GetErrorCountString());
			if (Result->second == 0)
			{

				Operator = ReciveRelationalOperator(code, Index);
				String^ MassagesConsole = gcnew String(Operator.c_str());
				Console::WriteLine("Here is an Operator {0}", MassagesConsole);
				// checking for spacial case 
				if (Operator[0] == '!' && Operator.size() == 1)
				{
					Token Unary(Operator, Compiler::UNARY_LOGICAL_OPERATOR, LineNumber);
					Tokens.emplace_back(Unary);
					return true;
				}
				// checking for '=' 
				else if (Operator[0] == '=' && Operator.size() > 1 && Operator[1] != '=')
				{
					Token RelationToken(Operator, Compiler::ASSIGN_OPERATOR, LineNumber);
					Tokens.emplace_back(RelationToken);
					return true;
				}
				else
				{
					Token RelationToken(Operator, Compiler::RELATIONAL_OPERATOR, LineNumber);
					Tokens.emplace_back(RelationToken);
					return true;
				}
			}
			else if (Result->second == 1)
			{
				// creates logical operators
				bool isValid = CheckOperatorValid(code, Index, Operator);
				if (isValid)
				{
					Token LogicalOp(Operator, Compiler::Token_Type::LOGICAL_OPERATOR, LineNumber);
					Tokens.emplace_back(LogicalOp);
					Index += 2;
					return true;
				}
				else
				{
					std::string ErrorLine = GetLine(code, Index);
					if (!m_refErrrorsMod->AddLexError(LineNumber, INVALID_OP_LOG, ErrorLine))
					{
						return false;
					}
					System::String^ Error = gcnew String(ErrorLine.c_str());
					Console::WriteLine("Generated Error Logical Operator {0}", Error);
					Index++;
					return true;
				}
			}
			else if (Result->second == 2)
			{
				if (FiguerOutOperator(Result->first, LineNumber, Tokens))
				{
					Index++;
				}
			}

			return true;
		}
	}

	return false;
}

void LexIndentifyOperator::ChangeState(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& Tokens, std::map<std::string, std::string>* Keywords, int SelectedState)
{}

std::string LexIndentifyOperator::ReciveRelationalOperator(const char * code, uint32_t & Index)
{
	std::string Result("");
	Result += code[Index];
	// check for equal sign
	if (code[Index + 1] == '=')
	{
		Result += '=';
		Index += 2;// moving to somewhere we haven't checked
	}
	else
	{
		Index++;
	}

	return Result;
}

bool LexIndentifyOperator::CheckOperatorValid(const char * code, uint32_t & Index, std::string & ResultingOperator)
{
	bool isValidOperator = false;
	std::array<char, 2> ValidOperators = { '|','&' };

	if (code[Index] == ValidOperators[0]) { isValidOperator = true; }
	if (code[Index] == ValidOperators[1]) { isValidOperator = true; }

	if (isValidOperator == false)
	{
		return false;
	}

	// check if the operator repeats
	if ((code[Index] != '\0' || code[Index + 1] != '\0') && code[Index] == code[Index + 1])
	{
		ResultingOperator = code[Index];
		ResultingOperator += code[Index + 1];
		PrintToConsole("Logical operator [{0}] ", ResultingOperator);
		return true;
	}
	else// return error
	{
		ResultingOperator = (code[Index]);
		PrintToConsole("NON-Logicla operator {0} ", ResultingOperator);
		return false;
	}
	return true;
}

bool LexIndentifyOperator::FiguerOutOperator(char Op, uint32_t LineNum, std::vector<Token>& Tokens)
{
	static std::map<char, Compiler::Token_Type> OperatorsAndDefinition = {
		{'+', Compiler::ARITHMETIC_OPERATOR}, { '-',Compiler::ARITHMETIC_OPERATOR }, { '*',Compiler::ARITHMETIC_OPERATOR },
		{ '/',Compiler::ARITHMETIC_OPERATOR }, { '%',Compiler::ARITHMETIC_OPERATOR }, { '^',Compiler::ARITHMETIC_OPERATOR },
	{ '[',Compiler::DIMENSION_OPERATOR }, {']',Compiler::DIMENSION_OPERATOR },{'(',Compiler::GROUPING_OPERATOR} ,
	{')',Compiler::GROUPING_OPERATOR} ,{'{',Compiler::GROUPING_OPERATOR},{'}',Compiler::GROUPING_OPERATOR},
	{'!',Compiler::UNARY_LOGICAL_OPERATOR} };

	auto PossibleToken = OperatorsAndDefinition.find(Op);

	// confirmed token 
	if (PossibleToken != OperatorsAndDefinition.end())
	{
		Console::WriteLine("Confirmed Operator {0}", ConvertChar(Op));
		char Lexema = PossibleToken->first;
		std::string Lex = "";
		Lex += Lexema;
		Token GenToken(Lex, PossibleToken->second, LineNum);
		Tokens.emplace_back(GenToken);

		return true;
	}

	return false;
}

bool LexIndentifyOperator::isOperator(char PossibleOperator)
{
	auto Result = Operators.find(PossibleOperator);

	if (Result != Operators.end())
	{
		return true;
	}

	return false;
}

std::map<char, int> LexIndentifyOperator::Operators = { {'<',0},{'>',0},{'!',0},{'=',0},
	{'|',1}, {'&',1} ,{'[',2} ,{']',2} ,
	{'+',2} ,{'-',2},{'*',2},{'%',2},{'/',2} ,{'^',2} ,
	{'{',2},{'}',2} , {'(',2} , {')',2} };