//--------------------<Include>
#include "Shell.h"
//===============================================================================


/*******************************************************************************/
/*                           Function implement                                */
/*******************************************************************************/
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

    }  else if (strcmp(Command, "mytype") == 0)
    {
        mytype(Command);

    } else
	{
		FindCommandInEnviroment(Command, Arguments, ArgNum, Options, OptnNum);
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

        env[c] = NULL;
        i = 0;
        Arguments[ArgNum] = Options[i];

        while ( i > (OptnNum - 1) )
        {
            i++;
            Arguments[ArgNum + i] = Options[i];
        }

        Arguments[ArgNum + i] = NULL;

        if ( execve((const char*)Command, (char* const)Arguments, (char* const)env ) == -1 )
        {
            printf("This command is not exit\n");
        }

        //Still in prograss depend on solving problem

	}    
}
