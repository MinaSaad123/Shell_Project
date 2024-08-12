#ifndef TEXTMANIPILATION_H
#define TEXTMANIPILATION_H

//----------------------<Include Libs>
#include "string.h"

//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//                                          Prototype
//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
void LooptoAfterNullTerminator(char* Str, int *Count);
void AddNullTerminator(char* Str, int Size);
int Remove_DuplctSpaces(char* String);
int  MyStrTok(char* Str, char Token);
#endif
