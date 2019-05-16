#include "stdafx.h"

#include "LexAnalyzer.h"
#include "ErrorsModule.h"

Compiler::LexAnalyzer::LexAnalyzer(ErrorsModule ^ Err)
{
	this->m_reErrrorsMod = Err;

	m_Keywords.insert(std::make_pair("var",""));
	/*m_Keywords.insert("int","");
	m_Keywords.insert("float","");
	m_Keywords.insert("string","");
	m_Keywords.insert("bool","");
	m_Keywords.insert("void","");
	m_Keywords.insert("function","");
	m_Keywords.insert("if","");
	m_Keywords.insert("else","");
	m_Keywords.insert("switch","");
	m_Keywords.insert("case","");
	m_Keywords.insert("default","");
	m_Keywords.insert("true","");
	m_Keywords.insert("false","");
	m_Keywords.insert("print","");
	m_Keywords.insert("read","");
	m_Keywords.insert("return","");
	m_Keywords.insert("inc","");
	m_Keywords.insert("dec","");*/
}

Compiler::LexAnalyzer::~LexAnalyzer()
{
}

bool Compiler::LexAnalyzer::ParseSourceCode(const char * srcCode)
{
	std::string Temp = srcCode;


	return true;
}

void Compiler::LexAnalyzer::clearToken()
{}

void Compiler::LexAnalyzer::getTokens(std::vector<Token*>* TokensVec)
{}

Token * Compiler::LexAnalyzer::getNextToken()
{
	return nullptr;
}

Token * Compiler::LexAnalyzer::getPrevToken()
{
	return nullptr;
}

Token * Compiler::LexAnalyzer::peckToken()
{
	return nullptr;
}
