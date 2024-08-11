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
void Parsing_Commandline(char* pCommandLine, int NumOfStr, char **Command, char *Arg[15], int *ArgNum, char* Optn[15], int *OptnNum, char *OutputRedir[], int* OutputRedirNum, int* OutputErorrRedir[], int* OutputErorrRedirNum, char* InputRedir[], int* InputRedirNum);

#endif
