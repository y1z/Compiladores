#include "stdafx.h"
#include "SemanticAnalysis.h"

Compiler::SemanticAnalysis::SemanticAnalysis()
{}

Compiler::SemanticAnalysis::~SemanticAnalysis()
{}

void Compiler::SemanticAnalysis::AddExplog(std::vector<Token*> &Expression, const std::string &FunctionName)
{}

void Compiler::SemanticAnalysis::CheckExpressions()
{}

std::map<const string, std::vector<Token*>> Compiler::SemanticAnalysis::GetExpresionContainer() const
{
	return m_ExpressionTokens;
}
