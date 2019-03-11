/* Andre augusto Giannotti Scota
 * andre.scota@gmail.com
 *
 * A Duble Linked List API
 *
 * Public Doamin
 *
 */


/* dubleLinkedList.h
 * A Duble Linked List implementation
 *
 *
 *  Who     | When       | What
 *  --------+------------+----------------------------
 *   a2gs   | 22/05/2005 | Creation
 */

#ifndef __A2GS_LINKED_LIST_H__
#define __A2GS_LINKED_LIST_H__


/* *** INCLUDES *** */


/* *** DEFINES *** */
#define A2GS_LINKEDLIST_OK						(1)
#define A2GS_LINKEDLIST_ERRO					(0)
#define A2GS_LINKEDLIST_ERROMSG_SIZE		(128)

#define A2GS_LINKEDLIST_MSG1 ("Falha malloc() to add node: [%s]")
#define A2GS_LINKEDLIST_MSG2 ("End fetch")
#define A2GS_LINKEDLIST_MSG3 ("Falha malloc() to add value node: [%s]")
#define A2GS_LINKEDLIST_MSG4 ("Unknow node")
#define A2GS_LINKEDLIST_MSG5 ("There are not nodes to delete")


/* *** DATA TYPES *** */
typedef enum{
	a2gs_LinkedList_EOk = 1, /* No error */
	a2gs_LinkedList_EAllocMemory, /* Erro Allocing dynamic memory */
	a2gs_LinkedList_ENoMoreNodes, /* End Fetch return */
	a2gs_LinkedList_EUnknowNode /* Cant find node position */
}a2gs_LinkedList_Erro_t;

typedef struct _a2gs_LinkedList_Node_t{
	struct _a2gs_LinkedList_Node_t *prev, *next; /* Previous and next nodes */
	void *value;                                 /* Value */
}a2gs_LinkedList_Node_t;

typedef struct _a2gs_LinkedList_Control_t{
	a2gs_LinkedList_Node_t *start, *now, *end;     /* Important list Address */
	unsigned long total;                           /* Total nodes */
	a2gs_LinkedList_Erro_t erro;                   /* Last error */
	char erroMsg[A2GS_LINKEDLIST_ERROMSG_SIZE+ 1]; /* Last error string msg */
}a2gs_LinkedList_Control_t;


/* *** INTERFACES / PROTOTYPES *** */
	/* <function>
	 *
	 * <Description>
	 *
	 * INPUT:
	 *  <None>
	 * OUTPUT:
	 *  <None>
	 */


/* *** EXAMPLE *** */
	#if 0
	#endif
#endif
