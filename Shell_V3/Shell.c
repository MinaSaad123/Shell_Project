//--------------------<Include>
#include "Shell.h"
//===============================================================================

/*******************************************************************************/
/*                                   macros                                    */
/*******************************************************************************/
#define STDIN    0
#define STDOUT   1
#define STDERROR 2

/*******************************************************************************/
/*                             Global variables                                */
/*******************************************************************************/
element_type* Command_Buf[10];
FIFO_buf_t Ready_Queue;
FIFO_buf_status Error;
/*******************************************************************************/
/*                           Function implement                                */
/*******************************************************************************/
void Display_ShellMessage(char* ShellMessage)
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
}

void Shell_Init()
{
    if ( FIFO_buf_init(&Ready_Queue, Command_Buf, 10) != FIFO_No_Error )
    {
        Error = FIFO_Init_Error;
    }

}

void Parsing_Commandline(char* pCommandLine, int NumOfStr, char **Command, char *Arg[15], int *ArgNum, char* Optn[15], int *OptnNum, char *OutputRedir[], int* OutputRedirNum, int* OutputErorrRedir[], int* OutputErorrRedirNum, char* InputRedir[], int* InputRedirNum)
{
    int i = 0;
    int NumOfPipe = 0;
    char* Ptr = pCommandLine;
    *ArgNum = 0;
    *OptnNum  = 0;
    *InputRedirNum = 0;
    *OutputRedirNum = 0;
    *OutputErorrRedirNum = 0;

    //*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

    //I know i can optimize size code but i have no time to manipulate with pointers again    

    //*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

    while (*Ptr != '\0')
    {
        if (*Ptr == '|')
        {
            NumOfPipe++;
        }
        Ptr++;
    }

    if (NumOfPipe == 0)
    {
        while ( ( *pCommandLine ) != '\0' && NumOfStr != 0)
        {
            if (i == 0)
            {
                *Command = pCommandLine;

                //Loop until Find NULL terminator.
                LooptoAfterNullTerminator(pCommandLine, &i);

            } else if ( pCommandLine[i] == '-')
            {
                Optn[*OptnNum] = (pCommandLine + i );
                (*OptnNum)++;

                //Loop until Find NULL terminator.
                LooptoAfterNullTerminator(pCommandLine, &i);

            } else if ( pCommandLine[i] == '>' )
            {
                i++;

                if ( pCommandLine[i] == '\0' ) 
                {
                    i++;
                }

                OutputRedir[*OutputRedirNum] = ( pCommandLine + i );
                *OutputRedirNum += 1;

                //Loop until Find NULL terminator.
                LooptoAfterNullTerminator(pCommandLine, &i);

            } else if ( pCommandLine[i] == '2' && pCommandLine[i + 1] == '>' )
            {
                i += 2;
            
                if ( pCommandLine[i] == '\0' )
                {
                    i++;
                }

                OutputErorrRedir[*OutputErorrRedirNum] = ( pCommandLine + i );
                *OutputErorrRedirNum += 1;

                //Loop until Find NULL terminator.
                LooptoAfterNullTerminator(pCommandLine, &i);

            } else if (pCommandLine[i] == '<')
            {
                i++;

                if ( pCommandLine[i] == '\0' )
                {
                    i++;
                }

                InputRedir[*InputRedirNum] = ( pCommandLine + i );
                *InputRedirNum += 1;

                //Loop until Find NULL terminator.
                LooptoAfterNullTerminator(pCommandLine, &i);

            } else
            {
                Arg[*ArgNum] = (pCommandLine + i );
                (*ArgNum)++;

                //Loop until Find NULL terminator.
                LooptoAfterNullTerminator(pCommandLine, &i);
            }

            NumOfStr--;
        } 

    } else if ( NumOfPipe > 0 )
    {
        int flag = 0;
        MyCommand TempCommand;

        while ( ( *pCommandLine ) != '\0' && NumOfStr != 0)
        {
            if ( (*pCommandLine) == '|' )
            {
                flag = 1;
                /*Continue coding here*/


            } else if (i == 0 ||  flag == 1)
            {
                flag = 0;
                TempCommand.Command = pCommandLine;

                //Loop until Find NULL terminator.
                LooptoAfterNullTerminator(pCommandLine, &i);


            } else if ( pCommandLine[i] == '-')
            {
                TempCommand.Options[TempCommand.OptnNum] = (pCommandLine + i );
                TempCommand.OptnNum++;

                //Loop until Find NULL terminator.
                LooptoAfterNullTerminator(pCommandLine, &i);

            } else if ( pCommandLine[i] == '>' )
            {
                i++;

                if ( pCommandLine[i] == '\0' ) 
                {
                    i++;
                }

                OutputRedir[*OutputRedirNum] = ( pCommandLine + i );
                *OutputRedirNum += 1;

                //Loop until Find NULL terminator.
                LooptoAfterNullTerminator(pCommandLine, &i);

            } else if ( pCommandLine[i] == '2' && pCommandLine[i + 1] == '>' )
            {
                i += 2;
            
                if ( pCommandLine[i] == '\0' )
                {
                    i++;
                }

                OutputErorrRedir[*OutputErorrRedirNum] = ( pCommandLine + i );
                *OutputErorrRedirNum += 1;

                //Loop until Find NULL terminator.
                LooptoAfterNullTerminator(pCommandLine, &i);

            } else if (pCommandLine[i] == '<')
            {
                i++;

                if ( pCommandLine[i] == '\0' )
                {
                    i++;
                }

                InputRedir[*InputRedirNum] = ( pCommandLine + i );
                *InputRedirNum += 1;

                //Loop until Find NULL terminator.
                LooptoAfterNullTerminator(pCommandLine, &i);

            } else
            {
                TempCommand.Arguments[TempCommand.ArgNum] = (pCommandLine + i );
                TempCommand.ArgNum++;

                //Loop until Find NULL terminator.
                LooptoAfterNullTerminator(pCommandLine, &i);
            }
            NumOfStr--;
        }
    }
}

int Default_FileDescriptor(int* Default_fd)
{
    if ( dup2(*Default_fd, STDIN) == -1 )
    {
        perror("dup2");
        close(*Default_fd);
        return -1;
    }

    if ( dup2(*Default_fd, STDOUT) == -1 )
    {
        perror("dup2");
        close(*Default_fd);
        return -1;
    }

    if ( dup2(*Default_fd, STDERROR) == -1 )
    {
        perror("dup2");
        close(*Default_fd);
        return -1;
    }
    
    close(*Default_fd);

    *Default_fd = 0;
}

void SelectCommand(char* Command, char *Arguments[], int ArgNum, char *Options[], int OptnNum)
{
	if (strcmp(Command, "mypwd") == 0)
	{

		mypwd(ArgNum, OptnNum);

	} else if (strcmp(Command, "myecho") == 0)
	{

		myecho(Arguments, ArgNum, Options, OptnNum);

	} else if (strcmp(Command, "mycp") == 0)
	{
		mycp(Arguments, ArgNum, Options, OptnNum);

	} else if (strcmp(Command, "mymv") == 0)
	{

		mymv(Arguments, ArgNum, Options, OptnNum);

	} else if (strcmp(Command, "myhelp") == 0)
	{
		myhelp(ArgNum, OptnNum);
	
	} else if (strcmp(Command, "myexit") == 0)
	{
		myExit(ArgNum, OptnNum);

	} else if (strcmp(Command, "mycd") == 0)
	{
		mycd(Arguments, ArgNum, Options, OptnNum);

	} else if (strcmp(Command, "myenvir") == 0)
    {
        myenvir(ArgNum, OptnNum);

    } else if (strcmp(Command, "myuptime") == 0) 
    {
        myuptime(ArgNum, OptnNum);

    } else if (strcmp(Command, "mytype") == 0)
    {
        mytype(Arguments, ArgNum);


    } else if (strcmp(Command, "myfree") == 0)
    {
        myfree(ArgNum, OptnNum);

    } else
	{
		FindCommandInEnviroment(Command, Arguments, ArgNum, Options, OptnNum);
	}
}

void Execute_Assign_operation(char** ppCommandLine, int* NumOfStr)
{
    int i = 0, flag = 0, AssignNumLeft = 0, AssignNum = 0, OffCheck = 0;
    char *Ptr = *ppCommandLine;
    char *arr[15];
    char* LocalVal, *LocalVar;

    while ( i < *NumOfStr )
    {
        arr[i] = Ptr;

        while ( *Ptr != '\0' )
        {
            if (*Ptr == '=' && OffCheck == 0)
            {
               AssignNumLeft++; 
               OffCheck = 1;
            }

            Ptr++;
        }

        if ( AssignNumLeft > AssignNum )
        {
            AssignNum = AssignNumLeft;
            OffCheck = 0;

        } else if ( AssignNum == AssignNumLeft)
        {
            flag = 1;
            break;
        }
        
        Ptr++;
        i++;
    }

    if (flag == 0)
    {
        i = 0;

        if ( AssignNumLeft != 0 )
        {
            while ( i < AssignNumLeft )
            {
                LocalVar = arr[i];
                
                while ( *arr[i] != '=' )
                {
                    arr[i]++;
                }

                *arr[i] = '\0';
                LocalVal = ++arr[i];
                Create_LocalVal_Node(LocalVar, LocalVal);

                i++;
            }

            *NumOfStr = 0;
        }
        
    } else if (flag == 1)
    {
        *NumOfStr -= AssignNumLeft;
        *ppCommandLine = arr[AssignNumLeft];
    }
}

void Replace_Variable_With_corresponding_Value(char** Command, char *Arguments[], int ArgNum)
{
    int i = 0;
    char* pArg = NULL, *Temp  = NULL, *pCommand;

    if (*Command[0] == '$')
    {
        pCommand = *Command;
        pCommand++;
        if ( ( Temp = FindLocalVar(pCommand) ) == NULL )
        {
            //Try to find it in enviroment

        } else
        {
            *Command = Temp;
        }
    }
    while ( i < ArgNum )
    {
        if ( *Arguments[i] == '$' )
        {
            pArg = Arguments[i];
            pArg++;

            if ( ( Temp = FindLocalVar(pArg) ) == NULL )
            {
                //Try to find it in enviroment

            } else
            {
                Arguments[i] = Temp;
            }
        }
        i++;
    }
}

void FindCommandInEnviroment(char* Command, char *Arguments[], int ArgNum, char *Options[], int OptnNum)
{
    /***************************************************/
    /*        i pass my own enviroment file            */
    /***************************************************/

    pid_t ID = 0;

    ID = fork();
    if (ID == -1)
    {
        perror("External command");

    } else if (ID > 0) /*That is the parent*/
    {
        pid_t status;

        wait(&status);

    } else if (ID == 0)  /*That is the child*/
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

        while ( Ptr[0] != '\n' )
        {

            env[c] = Ptr;

            while ( Ptr[0] != ':' )
            {
				if ( Ptr[0] == '\n' )
				{
					break;
				}

                Ptr++;
            }

			if (Ptr[0] == ':')
			{
                Ptr[0] = '\0';
			    Ptr++;
                c++;
			}
        }
		Ptr[0] = '\0';
        c++;
        env[c] = NULL;

        for (i = ArgNum - 1; i >= 0; i--)
        {
            Arguments[i + 1] = Arguments[i];
        }

        i = 0;
        ArgNum += 1;
        Arguments[0] = Command;

        if ( OptnNum != 0 )
        {
            while ( i < OptnNum )
            {        
                Arguments[ArgNum + i] = Options[i];
                i++;
            }

             Arguments[ArgNum + i] = NULL;
        }

        if ( execvpe((const char*)Command, (char* const)Arguments, (char* const)env ) == -1 )
        {
            printf("This command is not exist\n");
        }
	}    
}

void Redirect_FileDescriptors(char *OutputRedir[], int OutputRedirNum, char* OutputErorrRedir[], int OutputErorrRedirNum, char* InputRedir[], int InputRedirNum , int* default_fd)
{
    int i = 0, fd = 0;

    while (i < InputRedirNum)
    {
        if ( ( fd = open(InputRedir[i], O_CREAT | O_RDONLY | O_TRUNC, 0644) ) == -1 )
        {
            perror("open");
            return;
        }

        if ( *default_fd == 0 )
        {
            *default_fd = dup(STDIN);
        }

        if ( dup2(fd, STDIN) != STDIN )
        {
            perror("dup2");

            if ( close(fd) == -1 )
            {
                perror("close");
            }

            return;
        }

        if ( close(fd) == -1 )
        {
            perror("close");
            return;
        }

        i++;
    }


    i = 0;
    while (i < OutputRedirNum)
    {
        if ( ( fd = open(OutputRedir[i], O_CREAT | O_WRONLY | O_TRUNC, 0644) ) == -1 )
        {
            perror("open");
            return;
        }

        if ( *default_fd == 0 )
        {
            *default_fd = dup(STDOUT);
        }

        if ( dup2(fd, STDOUT) != STDOUT )
        {
            perror("dup2");

            if ( close(fd) == -1 )
            {
                perror("close");
            }

            return;
        }
  
        if ( close(fd) == -1 )
        {
            perror("close");
            return;
        }

        i++;
    }

    i = 0;
    while (i < OutputErorrRedirNum)
    {
        if ( ( fd = open(OutputErorrRedir[i], O_CREAT | O_WRONLY | O_TRUNC, 0644) ) == -1 )
        {
            perror("open");
            return;
        }

        if ( *default_fd == 0 )
        {
            *default_fd = dup(STDERROR);
        }

        if ( dup2(fd, STDERROR) != STDERROR )
        {
            perror("dup2");
            if ( close(fd) == -1 )
            {
                perror("close");
            }
            
            return;
        }

        if ( close(fd) == -1 )
        {
            perror("close");
            return;
        }

        i++;
    }
}
