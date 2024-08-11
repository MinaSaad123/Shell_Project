#ifndef SHELL_H
#define SHELL_H

//----------------------<Include Libs>
#include "TextManipilation.h"
#include "Commands.h"
#include "LocalVars_LinkedLists.h"
#include "Pipeline_FIFO.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
//==========================================================================================

/****************************************************************************************************/
/*                                        Function Protoype                                         */
/****************************************************************************************************/
void Shell_Init();
void Display_ShellMessage(char* ShellMessage);
void SelectCommand(char* Command, char *Arguments[], int ArgNum, char *Options[], int OptnNum);
void FindCommandInEnviroment(char* Command, char *Arguments[], int ArgNum, char *Options[], int OptnNum);
void Parsing_Commandline(char* pCommandLine, int NumOfStr, char **Command, char *Arg[15], int *ArgNum, char* Optn[15], int *OptnNum, char *OutputRedir[], int* OutputRedirNum, int* OutputErorrRedir[], int* OutputErorrRedirNum, char* InputRedir[], int* InputRedirNum);
void Execute_Assign_operation(char** ppCommandLine, int* NumOfStr);		
void Replace_Variable_With_corresponding_Value(char** Command, char *Arguments[], int ArgNum);
void Redirect_FileDescriptors(char *OutputRedir[], int OutputRedirNum, char* OutputErorrRedir[], int OutputErorrRedirNum, char* InputRedir[], int InputRedirNum , int* default_fd);
int  Default_FileDescriptor(int* Default_fd);
#endif
