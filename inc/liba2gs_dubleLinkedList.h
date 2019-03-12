/* Andre augusto Giannotti Scota
 * andre.scota@gmail.com
 *
 * A Duble Linked List (DLL) API
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

#ifndef __A2GS_DLL_LIST_H__
#define __A2GS_DLL_LIST_H__


/* *** INCLUDES *** */


/* *** DEFINES *** */
#define A2GS_DLL_OK						(1)
#define A2GS_DLL_ERRO					(0)
#define A2GS_DLL_ERROMSG_SIZE			(128)

#define A2GS_DLL_MSG1 ("Falha malloc() to add node: [%s]")
#define A2GS_DLL_MSG2 ("End fetch")
#define A2GS_DLL_MSG3 ("Falha malloc() to add value node: [%s]")
#define A2GS_DLL_MSG4 ("Unknow node")
#define A2GS_DLL_MSG5 ("There are not nodes to delete")

#define A2GS_DLL_GET_ERRORMSG(x)	(x->erroMsg)
#define A2GS_DLL_GET_ERRORCOD(x)	(x->erro)


/* *** DATA TYPES *** */
typedef enum{
	a2gs_DLL_EOk = 1,      /* No error */
	a2gs_DLL_EAllocMemory, /* Erro Allocing dynamic memory */
	a2gs_DLL_ENoMoreNodes, /* End Fetch return */
	a2gs_DLL_EUnknowNode  /* Cant find node position */
}a2gs_DLL_Erro_t;

typedef struct _a2gs_DLL_Node_t{
	struct _a2gs_DLL_Node_t *prev, *next; /* Previous and next nodes */
	void *value;                          /* Value */
}a2gs_DLL_Node_t;

typedef struct _a2gs_DLL_Control_t{
	a2gs_DLL_Node_t *start, *now, *end;     /* Important list Address */
	unsigned long total;                    /* Total nodes */
	a2gs_DLL_Erro_t erro;                   /* If a error had happen calling a dunction, this is the return */
	char erroMsg[A2GS_DLL_ERROMSG_SIZE+ 1]; /* If a error had happen calling a dunction, this is the error message */
}a2gs_DLL_Control_t;


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
int a2gs_DLL_Create(a2gs_DLL_Control_t **list);
void a2gs_DLL_StartWalk(a2gs_DLL_Control_t *list);
void * a2gs_DLL_Next(a2gs_DLL_Control_t *list);
void * a2gs_DLL_Previous(a2gs_DLL_Control_t *list);
int a2gs_DLL_AddNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize);
void * a2gs_DLL_GetLastValue(a2gs_DLL_Control_t *list);
int a2gs_DLL_RemoveNodeValue(a2gs_DLL_Control_t *list, a2gs_DLL_Node_t *node);
void * a2gs_DLL_GetCurrentNodeValue(a2gs_DLL_Control_t *list);
void * a2gs_DLL_GetValueFromThisNode(a2gs_DLL_Node_t *node);
a2gs_DLL_Node_t * a2gs_DLL_SearchNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize, unsigned int offset);
int a2gs_DLL_DeleteTopValue(a2gs_DLL_Control_t *list);
unsigned long a2gs_DLL_GetTotal(a2gs_DLL_Control_t *list);
int a2gs_DLL_DeleteBottomValue(a2gs_DLL_Control_t *list);
int a2gs_DLL_Delete(a2gs_DLL_Control_t *list);
void a2gs_DLL_Destroy(a2gs_DLL_Control_t *list);


/* *** EXAMPLE *** */
	#if 0
	#endif
#endif
