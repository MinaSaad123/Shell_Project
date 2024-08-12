#ifndef PIPELINE_FIFO_H
#define PIPELINE_FIFO_H

//-------------------_<Include>
#include "platform_types.h"
#include "stdlib.h"

//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//                                            User Define
//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
typedef struct
{
    char *  Command;
    char ** Arguments;
    char ** Options;
	char ** OutputRedir;
	char ** OutputErorrRedir;
	char ** InputRedir;
    int     ArgNum;
    int     OptnNum;
	int     OutputRedirNum;
	int     OutputErorrRedirNum;
	int     InputRedirNum;

} MyCommand;

//                          *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//--------------------------*                     Generic Macros                    *------------------------------
//                          *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
#define element_type MyCommand*

//=================================================================================================================

//==============<FIFO_buf_t structure>
typedef struct
{
	unsigned int length;
	unsigned int count;
	element_type* base;
	element_type* head;
	element_type* tail;

}FIFO_buf_t;

//==============<FIFO_buf_status enumeration>
typedef enum
{
	FIFO_No_Error,
	FIFO_Null,
	FIFO_Empty,
	FIFO_Full,
    FIFO_Init_Error

}FIFO_buf_status;

//                                           *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//===========================================*            Generic APIs           *========================================//
//                                           *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
void FIFO_print_buffer (FIFO_buf_t* FIFO_buf);
FIFO_buf_status FIFO_buf_is_full (FIFO_buf_t* FIFO_buf);
FIFO_buf_status FIFO_Clean_Queue (FIFO_buf_t* FIFO_buf );
FIFO_buf_status FIFO_buf_enqueue (FIFO_buf_t* FIFO_buf, element_type item);
FIFO_buf_status FIFO_buf_dequeue (FIFO_buf_t* FIFO_buf, element_type* item);
FIFO_buf_status FIFO_buf_init (FIFO_buf_t* FIFO_buf, element_type* buf, uint32_t Length);

#endif

