//-----------------------------------------------------<Include Libs>
#include <unistd.h>  //Necessary lib to use getcwd().
#include <stdlib.h>  //Necessary lib for malloc().
#include <stdio.h>   
#include <errno.h>   //Necessary lib for getcwd.
#include <string.h>  //Necessary lib to strlen
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>   //for open function
#include <dirent.h>
//===============================================================================

/*******************************************************************************/
/*                             Macros                                          */
/*******************************************************************************/
#define DataType char
#define STDOUT 1
#define STDIN  0
//===============================================================================

/*******************************************************************************/
/*                           Function implement                                */
/*******************************************************************************/
void pwd(int ArgNum, int OptnNum)
{
    char n = 100;
 	DataType* arr = (DataType*)malloc(n * sizeof(char));	

	if (ArgNum != 0 || OptnNum != 0)
	{
		printf("Too many argument \n"); //I use printf() to make easier.
		return;

	} 
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
        printf("\n");
}

void echo(char *Arg[], int ArgNum, char *Optn[], int OptnNum)
{	
	int i = 0;
	int printSpace = 0;
    int StrSize = 0;
	char* Temp_Ptr = NULL;

	while (Arg[i] != NULL)
	{
		if (printSpace == 1)
		{
			if (write(STDOUT, " ", 1) == -1)
       		{
       		    perror("echo");
 	   	  	 	return;
       		}
			printSpace = 0;
		}

		StrSize = strlen(Arg[i]);

		if (Arg[i][0] == '"' && Arg[i][StrSize - 1] == '"')
		{
			Temp_Ptr = Arg[i];
			Temp_Ptr[StrSize - 1] = '\0';
			Temp_Ptr++;
			printSpace++;
			
       		if (write(STDOUT, Temp_Ptr, StrSize - 1) == -1)
       		{
       		    perror("echo");
 	   	  	 	return;
       		}

		} else
		{
			if (write(STDOUT, Arg[i], StrSize) == -1)
       		{
       		    perror("echo");
 	   	  	 	return;
       		}

			printSpace++;
		}
		
		i++;
	}

    printf("\n");
}

void cp(char *Arg[], int ArgNum, char *Optn[], int OptnNum)  
{
	int fd1 = 0, fd2 = 0;
	char buf[300];
	int nread = 1;

	if (ArgNum != 2)
	{
		if (write(STDOUT, "Too many argument\n", strlen("Too many argument\n")) == -1)
       	{
       		perror("cp");
 	   	  	return;

       	}
	}
	if ( ( fd1 = open(Arg[0], O_RDONLY) ) == -1 )
	{
		perror("cp");
		return;

	}

	if ( ( fd2 = open(Arg[1], O_WRONLY) ) == -1 )
	{
		if ( close(fd1) == -1 )
		{
			perror("cp");
			return;
			
		}
		perror("cp");
		return;

	}
	if (OptnNum)
	{
		if (strcmp("-a", Optn[0]) == 0 || strcmp("--All", Optn[0]))   //Support one option.
		{
		
			printf("Not supported yet\n");

		} 

	} else
	{
		while (nread)
		{
			if ( (nread = read(fd1, buf, sizeof(buf) - 1) ) != -1)
			{
				if ( (write(fd2, buf, nread) ) == -1 )
				{
					perror("cp");
					close(fd1);
					close(fd2);
					return;
				} 

			} else
			{
				perror("cp");
				close(fd1);
				close(fd2);
				return;
			}
		}
	}
}

void mv(char *Arg[], int ArgNum, char *Optn[], int OptnNum)
{

	if (ArgNum != 2)
	{
		if (write(STDOUT, "Too many argument\n", strlen("Too many argument\n")) == -1)
       	{
       		perror("cp");
 	   	  	return;

       	}
	}


	if (OptnNum)
	{
		if (strcmp("-a", Optn[0]) == 0 || strcmp("--All", Optn[0]))   //Support one option.
		{
			printf("Not supported yet\n");

		} 

	} else
	{
		if ( ( rename(Arg[0], Arg[1]) ) == -1 )
		{
			perror("mv");
			return;
		}

	}

}

void help(int ArgNum, int OptnNum)
{
	char MyCommands[100] = "pwd\necho\ncp\nmv\nhelp\n";

	if (ArgNum != 0 || OptnNum != 0)
	{
		printf("Too many argument \n"); //I use printf() to make easier.
		return;

	} 
	if (write(STDOUT, MyCommands, strlen(MyCommands)) == -1)
    {
        perror("help");
        return;

    }
}

void MyExit(int ArgNum, int OptnNum)
{
	if (ArgNum != 0 || OptnNum != 0)
	{
		printf("Too many argument \n"); //I use printf() to make easier.
		return;

	} 

 	printf("Good Bye:)\n");
	exit(1);
}
//===============================================================================

