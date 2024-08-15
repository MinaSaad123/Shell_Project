//----------------------<Include Lib>
#include "LocalVars_LinkedLists.h"

//=============================================================================

//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//                              Global variables
//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
Node* Head = (Node*)NULL;
Node* Current = (Node*)NULL;
Node* GetNode = (Node*)NULL;
//=============================================================================

void Create_LocalVal_Node(char* LocalVar, char* LocalVal)
{
    
    Node* Temp = NULL;

    if ( ( Current = FindLocalVar(LocalVar) ) != NULL )
    {
        strcpy(Current->Local_Val, LocalVal);
        return;
    } 

    
    Temp = (Node*)malloc( sizeof(Head));

    strcpy(Temp->Local_Var, LocalVar);
    strcpy(Temp->Local_Val, LocalVal);

    if (Head == NULL)
    {
        Head = Temp;
        Current = Head;
        GetNode = Head;

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
                return pTemp;

            } else
            {
                pTemp = pTemp->pNext;
            }
        }

        return NULL;
    }
}


char* GetAllNodes()
{
    Node* Temp = NULL;

    if (GetNode == NULL)
    {
        Temp = GetNode;
        GetNode = Head;
        return Temp;
        
    } else 
    {
        Temp = GetNode;
        GetNode = GetNode->pNext;
        return Temp;
    }
}

