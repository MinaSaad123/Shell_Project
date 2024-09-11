//========================<Include>
#include "Pipeline_FIFO.h"

//                          *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//--------------------------*                     Generic Macros                    *------------------------------
//                          *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
#define NULL (void*)0


/*                                                |-------------------------|
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|   Function Implement    |-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 *                                                |-------------------------|
 */

//==========================================================================<FIFO_buf_init Function>
FIFO_buf_status FIFO_buf_init(FIFO_buf_t* FIFO_buf, element_type* buf, uint32_t Length)
{
	//checking if buffer is exist
	if (buf == NULL)     // if (!buf) --> Better in optimiztion
	{
		return FIFO_Null;
	}

	//Passing details for buffer
	FIFO_buf->base = buf;
	FIFO_buf->head = FIFO_buf->base;
	FIFO_buf->tail = FIFO_buf->base;
	FIFO_buf->count = 0;
	FIFO_buf->length = Length;

	return FIFO_No_Error;
}

//==========================================================================<FIFO_buf_enqueue Function>
FIFO_buf_status FIFO_buf_enqueue(FIFO_buf_t *FIFO_buf, element_type item)
{
	element_type Temp;
	int i = 0;

	if (FIFO_buf->base == NULL || FIFO_buf->head == NULL)
	{
		return FIFO_Null;

	} else if ((FIFO_buf->count == FIFO_buf->length))
	{
		return FIFO_Full;

	} else if (FIFO_buf->head == (FIFO_buf->base + (FIFO_buf->length - 1) )) //Circular Queue
	{
		Temp = (element_type*)malloc(sizeof(item));

		Temp->ArgNum = item->ArgNum;
		Temp->OptnNum = item->OptnNum;
		Temp->OutputRedirNum = item->OutputErorrRedirNum;
		Temp->InputRedirNum = item->InputRedirNum;

		// i can optimize this part in one function but not now.
		while ( i < ( Temp->ArgNum ) )  
		{
			Temp->Arguments[i] = item->Arguments[i];
			i++;
		}
		
		i = 0;
		while ( i < ( Temp->OptnNum ) )
		{
			Temp->Options[i] = item->Options[i];
			i++;
		}

		i = 0;
		while ( i < ( Temp->OutputRedirNum ) )
		{
			Temp->OutputRedir[i] = item->OutputRedir[i];
			i++;
		}

		i = 0;
		while ( i < ( Temp->OutputRedirNum ) )
		{
			Temp->OutputRedir[i] = item->OutputRedir[i];
			i++;
		}

		i = 0;
		while ( i < ( Temp->OutputErorrRedirNum ) )
		{
			Temp->OutputErorrRedir[i] = item->OutputErorrRedir[i];
			i++;
		}

		i = 0;
		while ( i < ( Temp->InputRedirNum ) )
		{
			Temp->InputRedir[i] = item->InputRedir[i];
			i++;
		}

		Temp->Command = item->Command;
		*(FIFO_buf->head) = Temp;
		FIFO_buf->head = FIFO_buf->base;

	} else
	{
		Temp = (element_type*)malloc(sizeof(item));

		Temp->ArgNum = item->ArgNum;
		Temp->OptnNum = item->OptnNum;
		Temp->OutputRedirNum = item->OutputErorrRedirNum;
		Temp->InputRedirNum = item->InputRedirNum;

		// i can optimize this part in one function but not now.
		while ( i < ( Temp->ArgNum ) )  
		{
			Temp->Arguments[i] = item->Arguments[i];
			i++;
		}
		
		i = 0;
		while ( i < ( Temp->OptnNum ) )
		{
			Temp->Options[i] = item->Options[i];
			i++;
		}

		i = 0;
		while ( i < ( Temp->OutputRedirNum ) )
		{
			Temp->OutputRedir[i] = item->OutputRedir[i];
			i++;
		}

		i = 0;
		while ( i < ( Temp->OutputRedirNum ) )
		{
			Temp->OutputRedir[i] = item->OutputRedir[i];
			i++;
		}

		i = 0;
		while ( i < ( Temp->OutputErorrRedirNum ) )
		{
			Temp->OutputErorrRedir[i] = item->OutputErorrRedir[i];
			i++;
		}

		i = 0;
		while ( i < ( Temp->InputRedirNum ) )
		{
			Temp->InputRedir[i] =  item->InputRedir[i];
			i++;
		}

		Temp->Command = item->Command;

		*(FIFO_buf->head) = Temp;
		FIFO_buf->head++;
	}

	FIFO_buf->count++;

	return FIFO_No_Error;
}

//==========================================================================<FIFO_buf_dequeue Function>
FIFO_buf_status FIFO_buf_dequeue(FIFO_buf_t *FIFO_buf, element_type* item)
{

	if (FIFO_buf->tail == ( FIFO_buf->base + ( FIFO_buf->length - 1) ) )
	{
		*item = *(FIFO_buf->tail);
		FIFO_buf->tail = FIFO_buf->base;
		FIFO_buf->count--;

	} else if (FIFO_buf->count == 0)
	{
		return FIFO_Empty;

	} else
	{
		*item = *(FIFO_buf->tail);
		FIFO_buf->tail++;
		FIFO_buf->count--;
	}

	return FIFO_No_Error;
}

//==========================================================================<FIFO_buf_is_full Function>
FIFO_buf_status FIFO_buf_is_full(FIFO_buf_t* FIFO_buf)
{
	if (FIFO_buf->count == FIFO_buf->length)
	{
		return FIFO_Full;
	}

	return FIFO_No_Error;
}

//==========================================================================<FIFO_buf_is_full Function>
FIFO_buf_status FIFO_Clean_Queue (FIFO_buf_t* FIFO_buf )
{
	FIFO_buf->head = FIFO_buf->base; //Return base to his start point ||OR FIFO_buf->head -= (FIFO_buf->count + 1)

	FIFO_buf->count = 0;  	/* Counts equal Zero */
	FIFO_buf->tail = FIFO_buf->base;

   return FIFO_No_Error;
}
