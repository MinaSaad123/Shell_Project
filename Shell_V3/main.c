//----------------------<Include Libs>
#include "Commands.h"
#include "Shell.h"
#include "TextManipilation.h"

//==========================================================================================

/******************************************************************************************/
/*                                        Macros                                          */
/******************************************************************************************/
#define STDOUT (int)1
#define STDIN  (int)0
#define Num    (int)15
//==========================================================================================

/******************************************************************************************/
/*                               Global variables for Shell                               */
/******************************************************************************************/
extern FIFO_buf_t Ready_Queue;
MyCommand * Temp = NULL;
MyCommand * Piped_Command = NULL;
char   ShellMessage[200]; 
char   CommandLine[110];         //This Buffer to store the writed line by user
char * Command = NULL;           //This array to store command
char * Options[Num];             //This array of pointers to store options
char * Arguments[Num];           //This array of Pointers to store Arguments
char * OutputRedir[10];
char * OutputErorrRedir[10];
char * InputRedir[10];
char * pCommandLine = NULL;
int    ArgNum = 0;
int    OptnNum = 0;
int    OutputRedirNum = 0;
int    OutputErorrRedirNum = 0;
int    InputRedirNum = 0;
int    default_fd = 0;
int    readSize = 0;
int    NumOfStr = 0;

//=======================================================================================

void main()
{
	Pipe_Mode_t Pipe_Mode;
	int i = 0, Count = 0;
	/***********************************************************************************/
	/*                                Core program                                     */
	/***********************************************************************************/

	//I- Init Shell -->  Read Username like ./bashrc file Init FIFO
	Shell_Init();
	//===================================================================================

	//II- While loop
	while(1)
	{	
		//1- Return file descriptor to it's default symbolic link
		if ( default_fd != 0)
		{
			if ( Default_FileDescriptor(&default_fd) == -1 )
			{
				printf("Shell: Error with file descriptor\n" );
				exit(1);	
			}
		}
		//===============================================================================
		
		//2- Display shell message
		Display_ShellMessage(&ShellMessage);
		//===============================================================================

		//3- Read from commandline
		if ( ( readSize = read(STDIN, CommandLine, 100) ) == -1 )
		{
			perror("Shell");
			exit(1);
		}
		pCommandLine = CommandLine;
		//===============================================================================

		//4- I will put Null Terminator at the end of code.
		AddNullTerminator(CommandLine, readSize);
		//===============================================================================


		//5- I will know clean my Buffer CommandLine from duplicated spaces.
		if (Remove_DuplctSpaces(CommandLine) == -1)
		{
			printf("%s[Enter]\n", ShellMessage);
		}

		//6- I will add NULL terminator instead of spaces.
		if (pCommandLine[0] != '\0')
		{
			if ( (NumOfStr = MyStrTok(CommandLine, ' ') ) == -1 )
			{
				printf("Error!\n");
				continue;
			} 

		} else
		{
			continue;
		}
		//===============================================================================

		//7- detect if there is assign variable and execute it.
		Execute_Assign_operation(&pCommandLine, &NumOfStr);		
		//===============================================================================
		
		//8- now i will get what is command, array of pointers for arrgument, argument number, array of pointers for arrgument option, option number.
		if ( NumOfStr == 0 )
		{
			continue;			
		}

		if (Parsing_Commandline(pCommandLine, NumOfStr, &Command, Arguments, (int*)&ArgNum, Options, (int*)&OptnNum, OutputRedir, (int*)&OutputRedirNum, OutputErorrRedir, (int*)&OutputErorrRedirNum, InputRedir, (int*)&InputRedirNum, &Pipe_Mode) == -1 )
		{
			while( FIFO_buf_dequeue(&Ready_Queue, &Temp) != NULL );

			continue;
		}
		//===============================================================================

		//9- detect if there is $variable and replace it's sample table.
		Replace_Variable_With_corresponding_Value(&Command, Arguments, ArgNum);
		//===============================================================================

		//10- now we can execute the program
		if (Pipe_Mode == Off)
		{
			// Change redirection if exit
			if (InputRedirNum != 0 || OutputErorrRedirNum != 0 || OutputRedirNum != 0) 
			{
				Redirect_FileDescriptors(OutputRedir, OutputRedirNum, OutputErorrRedir, OutputErorrRedirNum, InputRedir, InputRedirNum, &default_fd);
			}
			//===========================================================================

			// Select the command.
			SelectCommand(Command, Arguments, ArgNum, Options, OptnNum, Pipe_Mode);
			//============================================================================

		} else if (Pipe_Mode == On) //I try to support multi redirection within multi pipes but during implement i realize that it will take along time so i cancel it, and time is little.
		{
			if ( pipe(Pipe) == -1 )
			{
				perror("pipe");
				return;
			}

			for(i = 0; i < 2; i++)
			{
				if ( FIFO_buf_dequeue(&Ready_Queue, &Piped_Command) != NULL ) 
				{
					FindCommandInEnviroment(NULL, NULL, 0, NULL, 0, Piped_Command, On, Count);	
					Count++;
				}
			}

			Count  = 0;
		}
	}
    //===================================================================================
} 
//===================================================================
//(_   _)( )                   ( )       ( )   ( )               ( )
//  | |  | |__    ____   ___   | |/ )     \ \_/ /  ___    _   _  | |
//  | |  |  _  \ / _  )/  _  \ | | <        \ /   /   \  ( ) ( ) | |
//  | |  | | | |( (_| || ( ) | | |\ \       | |  ( (_) ) | (_) | | |
//  (_)  (_) (_) \___ )(_) (_) (_) (_)      (_)   \___/   \___/  (_)
