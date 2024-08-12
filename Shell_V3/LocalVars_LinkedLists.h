#ifndef LOCALVARS_LINKEDLISTS_H
#define LOCALVARS_LINKEDLISTS_H

//----------------------<Include Lib>
#include "stdlib.h"
#include "string.h"

//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//                              User Define
//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

struct LinkedList_Struct 
{
    char Local_Val[100];
    char Local_Var[100];
    struct LinkedList_Struct* pNext;

};

typedef struct LinkedList_Struct Node;


//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//                               Prototype
//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
void  Create_LocalVal_Node(char* Local_var, char* Local_Val);
char* FindLocalVar(char* LocalVar);
char* GetAllNodes();

#endif
