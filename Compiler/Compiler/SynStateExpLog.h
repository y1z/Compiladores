#pragma once

#include "ISynState.h"
#include "SemanticExpLog.h"

class Token;
// forward declaration

namespace Compiler {

	class SynStateExpLog : public ISynState
	{
	public:

		SynStateExpLog(LexAnalyzer *Lex,
			SyntaxAnalysis *Syn,
			ISynState *PrevState,
			SymbolsTable *Symblos,
			SemanticAnalysis *Semantic,
			const std::string &FunctionName,
			const string &Delimiter = ")");

		SynStateExpLog(LexAnalyzer *Lex,
			SyntaxAnalysis *Syn,
			ISynState *PrevState,
			SymbolsTable *Symblos,
			SemanticAnalysis *Semantic,
			const std::string &FunctionName,
			const Token *tokenFromAssigedState);

		~SynStateExpLog();

		bool CheckSyntax() override;
	private:
		//! make sure that it qualifies
		bool CheckForFunctionCall();
		// checking for negation
		bool CheckForNagation(const Token * Tok);
		//! to know what to check for 
		void ProcessTerm();
	private:
		//! to now if the expression has a '!'
		bool IsNegation;

		bool IsDone;
		// use this to check how many 
		int32_t m_CountParenthesis = 0;
		//! to give the semanticAnalisis the tokens it needs 
		//std::vector<const Token * > m_ExpressionTokens;
		//! this is where necessary information for logical expression 
		ExpLogData m_Data;

		std::vector<char > m_Parenthesis;

		string m_FunctionName;

		string m_SymbloToCheck{ "" };
		//! used to determine when to stop the logical expression 
		string m_Delimiter;
	};
}