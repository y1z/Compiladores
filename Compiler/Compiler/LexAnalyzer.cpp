#include "stdafx.h"
#include "LexAnalyzer.h"
#include "LexScannig.h"
#include "ErrorsModule.h"
#include "Utility.h"

Compiler::LexAnalyzer::LexAnalyzer(ErrorsModule ^ ErrorModule)
{
	this->m_refErrrorsMod = ErrorModule;
	// Here is all the keyword of the language
	m_Keywords.insert(std::make_pair("var", ""));
	m_Keywords.insert(std::make_pair("int", ""));
	m_Keywords.insert(std::make_pair("float", ""));
	m_Keywords.insert(std::make_pair("string", ""));
	m_Keywords.insert(std::make_pair("bool", ""));
	m_Keywords.insert(std::make_pair("void", ""));
	m_Keywords.insert(std::make_pair("function", ""));
	m_Keywords.insert(std::make_pair("if", ""));
	m_Keywords.insert(std::make_pair("else", ""));
	m_Keywords.insert(std::make_pair("switch", ""));
	m_Keywords.insert(std::make_pair("case", ""));
	m_Keywords.insert(std::make_pair("default", ""));
	m_Keywords.insert(std::make_pair("true", ""));//<- this one becomes a LOGICAL_CONSTANT
	m_Keywords.insert(std::make_pair("false", ""));//<- this one becomes a LOGICAL_CONSTANT
	m_Keywords.insert(std::make_pair("print", ""));
	m_Keywords.insert(std::make_pair("main", ""));
	m_Keywords.insert(std::make_pair("read", ""));
	m_Keywords.insert(std::make_pair("return", ""));
	m_Keywords.insert(std::make_pair("inc", ""));
	m_Keywords.insert(std::make_pair("dec", ""));
	m_Keywords.insert(std::make_pair("for", ""));
	m_Keywords.insert(std::make_pair("while", ""));

	m_CurrentToken = 0;
}

Compiler::LexAnalyzer::~LexAnalyzer()
{
	this->ClearToken();
	this->m_refErrrorsMod = nullptr;

}
//! Heres where the Parsing starts
bool Compiler::LexAnalyzer::ParseSourceCode(const char * srcCode)
{
	ILexerState *ptr_ScanningState = new LexScannig();
	uint32_t Index = 0;
	uint32_t LineCount = 1;//start value at 1 because it easer to understand
	ptr_ScanningState->m_refErrrorsMod = this->m_refErrrorsMod;
	// directly transfers all tokens to the LexAnalyzer 
	ptr_ScanningState->StateAction(srcCode, Index, LineCount, m_LexTokens, &m_Keywords);

	delete ptr_ScanningState;
	ptr_ScanningState = nullptr;
	return true;
}

void Compiler::LexAnalyzer::ClearToken()
{
	if (!m_LexTokens.empty())
	{
		m_LexTokens.clear();
	}
}

Token& Compiler::LexAnalyzer::GetNextToken()
{
	if (!((m_CurrentToken + 1) < (m_LexTokens.size() - 1)))
	{
		++m_CurrentToken;
		return m_LexTokens[m_CurrentToken];
	}

	return m_LexTokens[m_CurrentToken];
}

Token& Compiler::LexAnalyzer::GetPrevToken()
{
	if (!(m_CurrentToken - 1) <= 0)
	{
		--m_CurrentToken;
		return m_LexTokens[m_CurrentToken];
	}
	return m_LexTokens[m_CurrentToken];
}

Token& Compiler::LexAnalyzer::GetPeekToken()
{
	return m_LexTokens[m_CurrentToken];
}

Token Compiler::LexAnalyzer::PickToken(std::size_t Index)
{
	if (!((m_CurrentToken + 1) < (m_LexTokens.size() - 1)) && m_CurrentToken > -1)
	{
		return m_LexTokens[Index];
	}
	else
	{
		throw std::exception("OUT of Vector Bounds");
	}
	return Token();
}

std::size_t Compiler::LexAnalyzer::GetTokenCount()
{
	return m_LexTokens.size();
}

std::vector<Token> &Compiler::LexAnalyzer::GetTokenContainer()
{
	return m_LexTokens;
}

std::string Compiler::LexAnalyzer::GetTokenCountString(std::string &Result)
{
	Result = std::to_string(this->m_LexTokens.size());

	return Result;
}