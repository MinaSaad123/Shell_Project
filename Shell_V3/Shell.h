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
//====================================================================================================

//                        *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//------------------------*                     Generic Macros                    *-----------------//
//                        *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
#define NumOfBuiltInCommands 11
#define USERNAME "minasaad" // i can store this info in my enviroment but i did it like that to ease overhead implement.

//====================================================================================================

/*****************************************************************************************************/
/*                                     Global Variables                                              */
/*****************************************************************************************************/
char *BuiltInCommands[] = {"mypwd", "myecho", "mycp", "mymv", "mycd", "myhelp", "myenvir", "myuptime", "free" "myexit", "mytype", "allVar", "envir"};
int    Pipe[2] = {0, 0};
//====================================================================================================

typedef enum 
{
    Off,
    On

}Pipe_Mode_t;
/****************************************************************************************************/
/*                                        Function Protoype                                         */
/****************************************************************************************************/
void Shell_Init();
void Display_ShellMessage(char* ShellMessage);
void SelectCommand(char* Command, char *Arguments[], int ArgNum, char *Options[], int OptnNum, Pipe_Mode_t Pipe_Mode);
void FindCommandInEnviroment(char* Command, char *Arguments[], int ArgNum, char *Options[], int OptnNum, MyCommand * Piped_Command, Pipe_Mode_t Pipe_Mode, int Count);
void Execute_Assign_operation(char** ppCommandLine, int* NumOfStr);		
void Replace_Variable_With_corresponding_Value(char** Command, char *Arguments[], int ArgNum);
void Redirect_FileDescriptors(char *OutputRedir[], int OutputRedirNum, char* OutputErorrRedir[], int OutputErorrRedirNum, char* InputRedir[], int InputRedirNum , int* default_fd);
int  Parsing_Commandline(char* pCommandLine, int NumOfStr, char **Command, char *Arg[15], int *ArgNum, char* Optn[15], int *OptnNum, char *OutputRedir[], int* OutputRedirNum, int* OutputErorrRedir[], int* OutputErorrRedirNum, char* InputRedir[], int* InputRedirNum, Pipe_Mode_t* Pipe_State);
int  Default_FileDescriptor(int* Default_fd);
#endif
