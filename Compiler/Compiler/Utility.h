#pragma once
#include "ILexerState.h"
#include <string>
#include "Token.h"
/*! return an ascii representation */
wchar_t ConvertChar(char character);
/*! does not Advance the Index */
std::string GetLine(const char* code, uint32_t IndexCopy);
/*! check the char to see if it's an English letter*/
bool IsLetter(const char PossibleLetter);
/*! takes a char then tell me if it's a number or not*/
bool IsNumber(const char PossibleNumber);
/*! makes a const char * depending on the token  */
const char *TranslateToken(Compiler::Token_Type Token);
/*! Keeps moving the index until it find a char that not '\n' or '\r'*/
void IgnoreNewLineChar(const char* code, uint32_t & Index, uint32_t &LineNumber);
/*! sends the message to the console */
void PrintToConsole(const std::string &Message);
/*! sends a formated message to the console (can only have one {0}) inside the format)*/
void PrintToConsole(const char Format[], const std::string &Message);
/*! how im going to stop the lex analiser*/
bool CheckToStopLexAnalisis(msclr::gcroot<Compiler::ErrorsModule ^> m_refErrrorsMod);
//! this is to check a bunch of numbers 
bool IsNumberSequence(const std::string &Str);

bool SkipUntil(Compiler::LexAnalyzer *ptr_lex, const std::string &Delimiter);
//! this will help me identify what type is the current token 
string GetDataTypeFromToken(const Token * ptr_Tok);

bool MoveLexWithLambda(Compiler::LexAnalyzer *ptr_lex, const string &Delimter, bool(*Pred)(Compiler::LexAnalyzer *lex,const string &Delimiter));
//! move's the token one token index 
bool MoveAndAssignTokenIndex(Compiler::LexAnalyzer *ptr_Lex, const Token *&ptr_token);
//! this is used to compare the TokenTypes 
bool CompareTokenTypes(const Token *ptr_token, const char *Expected);
