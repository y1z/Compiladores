#include "stdafx.h"
#include "SemanticAnalysis.h"

namespace Compiler {

	SemanticAnalysis::SemanticAnalysis()
	{}

	SemanticAnalysis::~SemanticAnalysis()
	{}

	void SemanticAnalysis::AddExplog(ExpLogData &Data)
	{
		m_Expression.emplace_back(Data);
	}

	void SemanticAnalysis::CheckExpressions()
	{

		for(auto Expersion : m_Expression)
		{
			SemanticExpLog SemanTicLog(Expersion);
			m_Expression.push_back(SemanTicLog);
		}
		


	}

	std::vector<SemanticExpLog> SemanticAnalysis::GetExpresionContainer() const
	{
		return m_Expression;
	}


}