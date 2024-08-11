//----------------------<Include Lib>
#include "LocalVars_LinkedLists.h"

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
//=============================================================================

//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//                              Global variables
//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
Node* Head = (Node*)NULL;
Node* Current = (Node*)NULL;
//=============================================================================

void Create_LocalVal_Node(char* LocalVar, char* LocalVal)
{
    
    Node* Temp = (Node*)malloc( sizeof(Head) );

    if (Head == NULL)
    {
        Head = Temp;
        Current = Head;

    } else /*try to find last node*/
    {
        Current = Head;

        while (Current->pNext != NULL)
        {
            Current = Current->pNext;
        }

        Current->pNext = Temp;
        Current = Current->pNext;
    }

    if ( FindLocalVar(LocalVar) == NULL )
    {
        strcpy(Current->Local_Var, LocalVar);
        strcpy(Current->Local_Val, LocalVal);

    } else
    {
        strcpy(Current->Local_Val, LocalVal);
    }
}

char* FindLocalVar(char* LocalVar)
{
    Node* pTemp = NULL;

    if (Head == NULL)
    {
        return NULL;

    } else
    {
        pTemp = Head;

        while (pTemp != NULL)
        {
            if ( strcmp(LocalVar, pTemp->Local_Var) == 0 )
            {
                return pTemp->Local_Val;

            } else
            {
                pTemp = pTemp->pNext;
            }
        }

        return NULL;
    }
}

