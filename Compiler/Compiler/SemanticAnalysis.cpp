#include "stdafx.h"
#include "SemanticAnalysis.h"

Compiler::SemanticAnalysis::SemanticAnalysis()
{}

Compiler::SemanticAnalysis::~SemanticAnalysis()
{}

void Compiler::SemanticAnalysis::AddExplog(std::vector<const Token*> &Expression, const std::string &FunctionName)
{
	for (auto tok : Expression)
	{
		m_ExpressionTokens[FunctionName].emplace_back(tok);
	}
}

void Compiler::SemanticAnalysis::CheckExpressions()
{}

std::map<const string, std::vector<const Token*>> Compiler::SemanticAnalysis::GetExpresionContainer() const
{
	return m_ExpressionTokens;
}
