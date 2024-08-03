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
/*                             Global Variables                                */
/*******************************************************************************/
char *BuiltInCommands[] = {"mypwd", "myecho", "mycp", "mymv", "mycd", "myhelp", "myenvir", "myexit", "mytype"};
//===============================================================================

/*******************************************************************************/
/*                           Function implement                                */
/*******************************************************************************/
void mypwd(int ArgNum, int OptnNum)
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
 		perror("mypwd");
 		return;

 	} else
 	{
 		if (write(STDOUT, arr, strlen(arr)) == -1)
 		{
 			perror("mypwd");
 			return;
 		}	
 	}
        printf("\n");
}

void myecho(char *Arg[], int ArgNum, char *Optn[], int OptnNum)
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
       		    perror("myecho");
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
       		    perror("myecho");
 	   	  	 	return;
       		}

		} else
		{
			if (write(STDOUT, Arg[i], StrSize) == -1)
       		{
       		    perror("myecho");
 	   	  	 	return;
       		}

			printSpace++;
		}
		
		i++;
	}

    printf("\n");
}

void mycp(char *Arg[], int ArgNum, char *Optn[], int OptnNum)  
{
	int fd1 = 0, fd2 = 0;
	char buf[300];
	int nread = 1;

	if (ArgNum != 2)
	{
		if (write(STDOUT, "Too many argument\n", strlen("Too many argument\n")) == -1)
       	{
       		perror("mycp");
 	   	  	return;

       	}
	}
	if ( ( fd1 = open(Arg[0], O_RDONLY) ) == -1 )
	{
		perror("mycp");
		return;

	}

	if ( ( fd2 = open(Arg[1], O_WRONLY) ) == -1 )
	{
		if ( close(fd1) == -1 )
		{
			perror("mycp");
			return;
			
		}
		perror("mycp");
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
					perror("mycp");
					close(fd1);
					close(fd2);
					return;
				} 

			} else
			{
				perror("mycp");
				close(fd1);
				close(fd2);
				return;
			}
		}
	}
}

void mymv(char *Arg[], int ArgNum, char *Optn[], int OptnNum)
{

	if (ArgNum != 2)
	{
		if (write(STDOUT, "Too many argument\n", strlen("Too many argument\n")) == -1)
       	{
       		perror("mycp");
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
			perror("mymv");
			return;
		}

	}

}

void mycd(char *Arg[], int ArgNum, char *Optn[], int OptnNum)
{
	if (ArgNum != 1)
	{
		if (write(STDOUT, "Too many argument\n", strlen("Too many argument\n")) == -1)
       	{
       		perror("mycp");
 	   	  	return;

       	}

	}

	if ( chdir(Arg[0]) == -1 )
	{
		perror("mycd");
	}

}

void myenvir(int ArgNum, int OptnNum)
{
	int fd = 0, nRead = 0;
    char readbuf[500];
    char buf[100];

	if (ArgNum != 0 || OptnNum != 0)
	{
		if (write(STDOUT, "Too many argument\n", strlen("Too many argument\n")) == -1)
       	{
       		perror("myenvir");
 	   	  	return;

       	}

	}

	if ( getcwd(buf, 100) == NULL )
 	{
 		perror("Shell");
 		return;

 	}

    strcat(buf, "/enviroment");  //To make the shell see the env file in her folder.

    if ( ( fd = open(buf, O_RDONLY) ) == -1 )
	{
		perror("myenvir");
		return;

    }

    if ( ( nRead = read(fd, readbuf, 500) ) == -1 )
    {
        perror("myenvir");
		return;

    } else
	{
		if ( write(STDOUT, readbuf, nRead) == -1 )
		{
			perror("myenvir");
			return;

		}
	}


}

void mytype(char* Command)
{
	int i = 0, flag = 0;

	for (i = 0; i < 9; i++)
	{
		if ( ( strcmp(Command, BuiltInCommands[i]) ) == 0 )
		{
			flag = 1;
		}
	}

	if (flag == 1)
	{
		if ( write(STDOUT, "This command is built-in", strlen(Command)) == -1 )
		{
			perror("mytype");
			return;
		}

	} else
	{
		int fd = 0, i = 0, c = 0;
        char readbuf[500];
        char buf[100];
        char *Ptr = NULL;
        char *env[15];

		if ( getcwd(buf, 100) == NULL )
 		{
 			perror("Shell");
 			return;

 		}

        strcat(buf, "/enviroment");  //To make the shell see the env file in her folder.

        if ( ( fd = open(buf, O_RDONLY) ) == -1 )
	    {
		    perror("External command");
		    return;

        }

        if ( read(fd, readbuf, 500) == -1 )
        {
           	perror("External command");
		    return;
        }

        Ptr = strstr(readbuf, "PATH=");
        Ptr += 5;

        while ( Ptr[i] != '\n' )
        {
            env[c] = Ptr;

            while ( Ptr != ':' )
            {
                Ptr++;
            }

            Ptr[i] = '\0';
            i++;
            c++;

        }

		


	}
}

void myhelp(int ArgNum, int OptnNum)
{
	char MyCommands[100] = "mypwd\nmyecho\nmycp\nmymv\nmycd\nmyenvir\nmyhelp\nmyexit\n";

	if (ArgNum != 0 || OptnNum != 0)
	{
		printf("Too many argument \n"); //I use printf() to make easier.
		return;

	} 
	if (write(STDOUT, MyCommands, strlen(MyCommands)) == -1)
    {
        perror("myhelp");
        return;

    }
}

void myExit(int ArgNum, int OptnNum)
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

