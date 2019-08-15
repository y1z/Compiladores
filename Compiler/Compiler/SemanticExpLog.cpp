#include "stdafx.h"
#include "SemanticExpLog.h"
namespace Compiler {

	SemanticExpLog::SemanticExpLog(ExpLogData &Data)
	:m_Data(Data)
	{}

	SemanticExpLog::~SemanticExpLog()
	{}

	void SemanticExpLog::BuildTree()
	{}

	void SemanticExpLog::ConvertInfixToPostFix()
	{
		string InfixNotation = "";

		for(size_t i = 0; i < m_Data.mptr_tokens.size() - 1; ++i)
		{
			InfixNotation += m_Data.mptr_tokens[i]->getLex();
		}
	}

	bool SemanticExpLog::ValidateTree()
	{
		return false;
	}

}