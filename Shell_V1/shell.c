//----------------------<Include Libs>
#include "Commands.h"
#include "TextManipilation.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
//==========================================================================================

/******************************************************************************************/
/*                                        Macros                                          */
/******************************************************************************************/
#define STDOUT (int)1
#define STDIN  (int)0
#define Num    (int)5
//==========================================================================================

/******************************************************************************************/
/*                               Global variables for Shell                               */
/******************************************************************************************/
char   ShellMessage[200]; 
char   CommandLine[110];         //This Buffer to store the writed line by user
char * Command = NULL;           //This array to store command
char * Options[Num];             //This array of pointers to store options
char * Arguments[Num];           //This array of Pointers to store Arguments
int    ArgNum = 0;
int    OptnNum = 0;

//==========================================================================================

/******************************************************************************************/
/*                                        Prototype                                       */
/******************************************************************************************/
void ExecuteCommandLine();
void SelectCommand();

//==========================================================================================

void main()
{
	/***********************************************************************************/
	/*                                Core program                                     */
	/***********************************************************************************/
	int readSize = 0;
	int NumOfStr = 0;
	while(1)
	{
		 	
		if ( getcwd(ShellMessage, 100) == NULL )
 		{
 			perror("Shell");
 			return;

 		}

		strcat(ShellMessage, "$ ");  //Concatinating Directory with "$".

		if( write(STDOUT, ShellMessage, strlen(ShellMessage) ) == -1 )  //Print message
		{
			perror("Shell:");
			exit(0);
		}
		
		if ( ( readSize = read(STDIN, CommandLine, 100) ) == -1 )
		{
			perror("Shell");
			exit(1);
		}
		
		//1- I will put Null Terminator at the end of code.
		AddNullTerminator(CommandLine, readSize);
		//===============================================================================

		//2- I will know clean my Buffer CommandLine from duplicated spaces.
		if (Remove_DuplctSpaces(CommandLine) == -1)
		{
			printf("%s[Enter]\n", ShellMessage);
		}

		//3- I will add NULL terminator instead of spaces.
		 if ( (NumOfStr = MyStrTok(CommandLine, ' ')) == -1 )
		 {
			printf("Error!\n");
			continue;
		 }
		//===============================================================================

		//4- know i will get what is command, array of pointers for arrgument, argument number, array of pointers for arrgument option, option number.
		SepArgOptnComm(CommandLine, NumOfStr, &Command, Arguments, (int*)&ArgNum, Options, (int*)&OptnNum);
		//===============================================================================


		//5- Know we can Execute the commandLine.
		//ExecuteCommandLine();
		SelectCommand();
		

	}
    //=========================================================================================

}

void SelectCommand()
{
	if (strcmp(Command, "pwd") == 0)
	{

		pwd(ArgNum, OptnNum);

	} else if (strcmp(Command, "echo") == 0)
	{

		echo(Arguments, ArgNum, Options, OptnNum);

	} else if (strcmp(Command, "cp") == 0)
	{
		cp(Arguments, ArgNum, Options, OptnNum);

	} else if (strcmp(Command, "mv") == 0)
	{

		mv(Arguments, ArgNum, Options, OptnNum);

	} else if (strcmp(Command, "help") == 0)
	{
		help(ArgNum, OptnNum);
	
	} else if (strcmp(Command, "exit") == 0)
	{
		MyExit(ArgNum, OptnNum);

	} else
	{
		printf("Command not found\n");
	}
}


