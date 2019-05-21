#pragma once
#include "ILexerState.h"
#include <string>

wchar_t ConvertChar(char character);
/*! does not Advance the Index */
std::string GetErrorLine(const char* code, uint32_t IndexCopy);

void TrasferToken(ILexerState *Reciver, ILexerState *Giver);

bool IsLetter(const char PossibleLetter);
/*! takes a char then tell me if it's a number or not*/
bool IsNumber(const char PossibleNumber);