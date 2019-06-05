#include "stdafx.h"
#include "Utility.h"
#include "LexIndentifyOperator.h"


LexIndentifyOperator::LexIndentifyOperator()
{}


LexIndentifyOperator::~LexIndentifyOperator()
{}

bool LexIndentifyOperator::StateAction(const char * code, uint32_t & Index, uint32_t & LineNumber, std::vector<Token>& m_GeneratedTokens, std::map<std::string, std::string>* Keywords)
{
	/*
	char = the operator
	int = Methods used the check operator (it could have a = to it right )
	0 = check for equals sign
	1 = check for repeat
	2 = alone
	*/
	static std::map<char, int> Operators = { {'<',0},{'>',0},{'!',0},{'=',0},
	{'|',1}, {'&',1} ,{'[',2} ,{']',2} ,
	{'+',2} ,{'-',2},{'*',2},{'%',2},{'/',2} ,{'^',2} ,
	{'{',2},{'}',2} , {'(',2} , {')',2} };

	auto Result = Operators.find(code[Index]);

	Console::WriteLine("Fond char {0}", ConvertChar(code[Index]));
	if (Operators.end() != Result)
	{
		std::string Operator;
		// creates Relational operators
		if (Result->second == 0)
		{

			Operator = ReciveRelationalOperator(code, Index);
			// checking for spacial case 
			if (Operator[0] == '!' && Operator.size() == 1)
			{
				Token Unary(Operator, Compiler::UNARY_LOGICAL_OPERATOR, LineNumber);
				m_GeneratedTokens.emplace_back(Unary);
				return true;
			}
			// checking for '=' 
			else if (Operator[0] == '=' && Operator.size() > 1 && Operator[1] != '=')
			{
				Token RelationToken(Operator, Compiler::ASSIGN_OPERATOR, LineNumber);
				m_GeneratedTokens.emplace_back(RelationToken);
				return true;
			}
			else
			{
				Token RelationToken(Operator, Compiler::RELATIONAL_OPERATOR, LineNumber);
				m_GeneratedTokens.emplace_back(RelationToken);
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
				m_GeneratedTokens.emplace_back(LogicalOp);
				return true;
			}
			else
			{
				std::string ErrorLine = GetErrorLine(code, Index);
				m_refErrrorsMod->AddLexError(LineNumber, INVALID_OP_LOG, ErrorLine);
				System::String^ Error = gcnew String(ErrorLine.c_str());
				Console::WriteLine("Generated Error Logical Operator {0}", Error);
				return true;
			}
		}
		else if (Result->second == 2)
		{
			FiguerOutOperator(Result->first, LineNumber);
			for (Token tok : m_GeneratedTokens)
			{
				m_GeneratedTokens.emplace_back(tok);
			}
		}

		return true;
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

bool LexIndentifyOperator::CheckOperatorValid(const char * code, uint32_t & Index, std::string & PosibleOperator)
{
	// check if the operator repeats
	if (code[Index] == code[Index + 1])
	{
		PosibleOperator = (code[Index] + code[Index + 1]);
		return true;
	}
	else// return error
	{
		PosibleOperator = (code[Index]);
		return false;
	}

	return true;
}


bool LexIndentifyOperator::FiguerOutOperator(char Op, uint32_t LineNum)
{
	static std::map<char, Compiler::Token_Type> OperatorsAndDefinition = {
		{'+', Compiler::ARITHMETIC_OPERATOR}, { '-',Compiler::ARITHMETIC_OPERATOR }, { '*',Compiler::ARITHMETIC_OPERATOR },
		{ '/',Compiler::ARITHMETIC_OPERATOR }, { '%',Compiler::ARITHMETIC_OPERATOR }, { '^',Compiler::ARITHMETIC_OPERATOR },
	{ '[',Compiler::DIMENSION_OPERATOR }, {']',Compiler::DIMENSION_OPERATOR },{'(',Compiler::GROUPING_OPERATOR} ,
	{')',Compiler::GROUPING_OPERATOR} ,{'{',Compiler::GROUPING_OPERATOR},{'}',Compiler::GROUPING_OPERATOR},{'!',Compiler::UNARY_LOGICAL_OPERATOR} };

	auto PossibleToken = OperatorsAndDefinition.find(Op);

	Console::WriteLine("Possible Operator  {0}", ConvertChar(Op));

	// confirmed token 
	if (PossibleToken != OperatorsAndDefinition.end())
	{
		Console::WriteLine("Confirmed Operator {0}", ConvertChar(Op));
		std::string Lex(&PossibleToken->first);
		Token GenToken(Lex, PossibleToken->second, LineNum);
		m_GeneratedTokens.emplace_back(GenToken);

		return true;
	}

	return false;
}
