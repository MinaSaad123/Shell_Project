//----------------------<Include Libs>
#include "TextManipilation.h"
#include "Commands.h"
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
void SelectCommand(char* Command, char *Arguments[], int ArgNum, char *Options[], int OptnNum);
void FindCommandInEnviroment(char* Command, char *Arguments[], int ArgNum, char *Options[], int OptnNum);


