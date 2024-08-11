//IMPORTANT NOTE:)
//MY Str functions is so simple and are made for specific purpose.

//----------------------<Include Libs>
#include "TextManipilation.h"

/*******************************************************************************/
/*                                Services function                            */
/*******************************************************************************/
void LooptoAfterNullTerminator(char* Str, int *Count)
{
    while (Str[*Count] != '\0')
    {
        (*Count)++;
    }

    (*Count)++;
}
//===============================================================================

void AddNullTerminator(char* Str, int Size)
{
    Str[Size - 1] = '\0';
}

int Remove_DuplctSpaces(char* Str)   //It Takes me alot of time in implemet and which makes it harder i dont know gdb command so i learned it.
{
    int i = 0, c = 0, d = 0;
    int SpaceCount  = 0;

    for (i = 0; Str[i] != '\0'; i++)
    {
        while ( Str[i] == ' ' ) //Count spaces.
        {
            SpaceCount++;
            i++;
        }
        if ( (SpaceCount != 0 && ( (i - SpaceCount) == 0) || (Str[i] == '\0') ) )
        {
            for (c = i; Str[c] != '\0'; c++)  //Reposition characters.
            {
                Str[c - SpaceCount] = Str[c];
            }

            for (d = SpaceCount; d != 0; d--) //Add NULL terminator instead of replaced String's position
            {
                Str[c - d] = '\0';
            }


        } else if (SpaceCount > 1)
        {
            SpaceCount--;

            for (c = i; Str[c] != '\0'; c++)  //Reposition characters.
            {
                Str[c - SpaceCount] = Str[c];
            }

            for (d = SpaceCount; d != 0; d--) //Add NULL terminator instead of replaced String's position
            {
                Str[c - d] = '\0';
            }    
        }        

        i -= SpaceCount;
        SpaceCount = 0;
    }

    if ( i == 0)
    {
        return -1;
    }
}

int MyStrTok(char* Str, char Token)
{
    int i = 0, c = 0;
    int NumOfStr = 1, Cou = 0, NumOfDubleQuo = 0;

    for (i = 0; Str[i] != '\0'; i++)
    {
        if (Str[i] == '"')
        {
            c = i + 1;

            while (Str[c] != '\0')
            {
                if (Str[c] == '"')  
                {
                    if (Str[c + 1] == Token)
                    {
                        Str[c + 1] = '\0';
                        i = c + 1;
                        NumOfStr++;
                        NumOfDubleQuo++;
                        break;
                    } 

                } else if (Str[c + 1] == '\0')
                {
                    return -1;
                }
                
                c++;
            }

        }  else if (Str[i] == Token)
        {
            Str[i] = '\0';
            NumOfStr++;
        }
    }

    return NumOfStr;
}
