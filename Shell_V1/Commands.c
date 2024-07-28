#include <unistd.h>  //Necessary lib to use getcwd().
#include <stdlib.h>  //Necessary lib for malloc().
#include <stdio.h>   
#include <errno.h>   //Necessary lib for getcwd.
#include <string.h>  //Necessary lib to strlen
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  //for open function
#include <dirent.h>

//----------------------------------------
//                Macros
//----------------------------------------
#define DataType char
#define STDOUT 1
#define STDIN  0

//----------------------------------------
//               Extern Variable
//----------------------------------------               
extern char CommandLine[100];
extern char* Command;
extern char *arr[10];

//-----------------------------------------------------------------
//                        Services Function
//-----------------------------------------------------------------

static void HandlingCommandLine (char** PP_CommandLine)
{
	while ((**PP_CommandLine) != '\0')
	{
		(*PP_CommandLine)++;
	}

	(*PP_CommandLine)++;
}

static int ParsingOptions ()
{
	int Position = -1;
	if (Command != NULL)
	{
		int i = 0;
		(arr[i]) = strtok(NULL, " ");

		while ( (arr[i]) == NULL)
		{
			i++;
                        
			if (*(arr[i]) == '-')
			{
				Position;
			}
			
		}
	}

	return Position;
}

//---------------------------------------------------------------------------------------------------------------------------------------
void pwd ()
{
	char n = 100;
	DataType* arr = (DataType*)malloc(n * sizeof(char));	

	if ( getcwd(arr, 100) == NULL )
	{
		perror("pwd");
		return;

	} else
	{
		if (write(STDOUT, arr, strlen(arr)) == -1)
		{
			 perror("pwd");
			 return;
		}	
	}
}

void echo ()
{
	char* StrText = CommandLine;
	
	HandlingCommandLine(&StrText);
	
        if (write(STDOUT, StrText, strlen(StrText)) == -1)
        {
                perror("echo");
		return;
        }
}
void cp ()
{
	int Position, i, fd_Source = 0, fd_Destination = 0;
	int Read_Size, Write_Size;
        char* StrText = CommandLine;
	char Buffer[200];

        HandlingCommandLine(&StrText);  //Make pointer arrives to beyond null terminator
	
	/* Parsing to know where is option */
	Position = ParsingOptions();	
      
	/*Because there isn't time i will right now suppose the user always send one option*/
	if (Position == -1)  /* There is not option*/
	{
		fd_Source = open(arr[0], O_RDONLY);
		if ( fd_Source == -1)
		{
			perror("cp");
			return;
		}	
		
		fd_Destination = open(arr[1], O_WRONLY);
		if (fd_Destination == -1)
		{
			close(fd_Destination);
			perror("cp");
			return;
		}

		while (Read_Size = read(fd_Source, Buffer, strlen(Buffer)) > 0)
		{
			if (write(fd_Destination, Buffer, strlen(Buffer)) != Read_Size)
			{
				close(fd_Destination);
				close(fd_Source);
				perror("cp");
				return;
			}
		}
	} else if (strcmp((arr[Position]), "-a") == 0) /* User pass option -a */
	{
		printf("Not supported yet\n");
	} 
}

void help ()
{
	char MyCommands[100] = "pwd\necho\ncp\nmv\nhelp";
	
	if (write(STDOUT, MyCommands, strlen(MyCommands)) == -1)
        {
                perror("pwd");
                return;
        }
}

void MyExit ()
{
 	printf("Good Bye:)\n");
	exit(1);
}

