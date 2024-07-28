#include "Commands.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

//----------------------------------------
//                Macros
//----------------------------------------
#define STDOUT 1
#define STDIN  0

//Global variables
char* Command;
int Flag = 0;
char *arr[10];
char CommandLine[100];
char* Shell_Init_Message = "Under ur services> ";

//Function prototype
void SelectCommand ();

void main ()
{
	char* Command;
	ssize_t ReadLength = 0;
	int i = 0;

	while (1)
	{
		if (write(STDOUT, Shell_Init_Message, strlen(Shell_Init_Message)) == -1)
		{
			perror("Shell");
			exit(1);  //Problem in shell itself ,thus there is no need to continue.
		}
	        ReadLength = read(STDIN, CommandLine, 100);
		CommandLine[ReadLength - 1] = '\0';

		if (ReadLength == -1)
	        {
			perror("Under ur services> ");
		        Flag ^= 1;
	        }
		
		if (Flag == 0)
		{	
			Command = strtok(CommandLine, " ");
		
		}	
		/* Function to praser which command**/
		SelectCommand();

                while (i == ReadLength)
                {
               	       CommandLine[i] = 'A';
                       i++;
                }

                i = 0;
		printf("\n");
        }
}


void SelectCommand ()
{
	if (strcmp(CommandLine, "pwd") == 0)
	{
		pwd();

	} else if (strcmp(CommandLine, "echo") == 0)
	{
		echo();

	} else if (strcmp(CommandLine, "cp") == 0)
	{
		cp();

	} else if (strcmp(CommandLine, "mv") == 0)
	{

		//mv();

	} else if (strcmp(CommandLine, "help") == 0)
	{
		help();
	
	} else if (strcmp(CommandLine, "exit") == 0)
	{
		
		MyExit();

	} else
	{
		printf("%s Command not found", Shell_Init_Message);
	}
}


