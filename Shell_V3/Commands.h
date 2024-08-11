#ifndef COMMANDS_H
#define COMMANDS_H

//-----------------------------------------------------<Include Libs>
#include <time.h>
#include <unistd.h>  //Necessary lib to use getcwd().
#include <stdlib.h>  //Necessary lib for malloc().
#include <stdio.h>   
#include <errno.h>   //Necessary lib for getcwd.
#include <string.h>  //Necessary lib to strlen
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>   //for open function
#include <dirent.h>
#include <sys/sysinfo.h>
//===============================================================================

/*******************************************************************************/
/*                             Macros                                          */
/*******************************************************************************/
#define DataType char
#define STDOUT 1
#define STDIN  0
//===============================================================================

//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//                                          Prototype
//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
void mypwd(int ArgNum, int OptnNum);
void myecho(char *Arg[], int ArgNum, char *Optn[], int OptnNum);
void mycp(char *Arg[], int ArgNum, char *Optn[], int OptnNum);
void mymv(char *Arg[], int ArgNum, char *Optn[], int OptnNum);
void myhelp(int ArgNum, int OptnNum);
void myenvir(int ArgNum, int OptnNum);
void myExit(int ArgNum, int OptnNum);
void mycd(char *Arg[], int ArgNum, char *Optn[], int OptnNum);
void mytype(char *Arg[], int ArgNum);
void myuptime(int ArgNum, int OptnNum);
void myfree(int ArgNum, int OptnNum);


#endif