#pragma once
#include "ISynState.h"

class Token;

namespace Compiler {

	class SynStateExpLog : public ISynState
	{
	public:

		SynStateExpLog(LexAnalyzer *Lex,
			SyntaxAnalysis *Syn,
			ISynState *PrevState,
			SymbolsTable *Symblos,
			SemanticAnalysis *Semantic,
			const std::string &FunctionName);

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
		// use this to check how many 
		int32_t m_ParenthesisLevel = 0;
		//! to give the semanticAnalisis the tokens it needs 
		std::vector<const Token * > m_ExpressionTokens;

		string m_FunctionName;
	};
}