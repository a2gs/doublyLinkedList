
/* Andre Augusto Giannotti Scota
 * andre.scota@gmail.com
 *
 * A Duble Linked List (DLL) API
 *
 * Public Doamin
 *
 */


/* dubleLinkedList.c
 * A Duble Linked List implementation
 *
 *
 *  Who     | When       | What
 *  --------+------------+----------------------------
 *   a2gs   | 22/05/2005 | Creation
 */


/* *** INCLUDES *** */
#include <stdio.h>
#include <string.h>
#include "liba2gs_dubleLinkedList.h"


/* *** DEFINES AND LOCAL DATA TYPE DEFINATION *** */
typedef struct _userType1_t{
	char a[10];
	int b;
}userType1_t;

typedef struct _userType2_t{
	char c[10];
	int d;
}userType2_t;


/* *** LOCAL PROTOTYPES *** */


/* *** EXTERNS / LOCAL GLOBALS *** */


/* ------------------------------------------------------------------------------------------- */

int main(int argc, char *argv[])
{
	a2gs_DLL_Control_t *list = NULL;
	userType1_t var1 = {"sample 1", 8};
	userType2_t var2 = {"sample 2", 13};
	int x = 10;
	char *s = "sample 3";
	a2gs_DLL_Node_t *walker = NULL;

	/*
---int a2gs_DLL_Create(a2gs_DLL_Control_t **list);
void a2gs_DLL_StartFetch(a2gs_DLL_Control_t *list);                                                                 
void * a2gs_DLL_Fetch(a2gs_DLL_Control_t *list);
---int a2gs_DLL_AddNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize);
void * a2gs_DLL_GetLastValue(a2gs_DLL_Control_t *list);
int a2gs_DLL_RemoveNodeValue(a2gs_DLL_Control_t *list, a2gs_DLL_Node_t *node);
void * a2gs_DLL_GetCurrentNodeValue(a2gs_DLL_Control_t *list);
void * a2gs_DLL_GetValueFromThisNode(a2gs_DLL_Node_t *node);
a2gs_DLL_Node_t * a2gs_DLL_SearchNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize, unsigned int offset);
int a2gs_DLL_DeleteTopValue(a2gs_DLL_Control_t *list);
---unsigned long a2gs_DLL_GetTotal(a2gs_DLL_Control_t *list);
int a2gs_DLL_DeleteBottomValue(a2gs_DLL_Control_t *list);
int a2gs_DLL_Delete(a2gs_DLL_Control_t *list);
void a2gs_DLL_Destroy(a2gs_DLL_Control_t *list);
*/


	if(a2gs_DLL_Create(&list) == A2GS_DLL_ERRO){
		printf("Erro creating DLL.\n");
		return(-1);
	}

	if(a2gs_DLL_AddNode(list, (userType1_t *) &var1, sizeof(userType1_t)) == A2GS_DLL_ERRO){
		return(-1);
	}
	a2gs_DLL_AddNode(list, (userType2_t *) &var2, sizeof(userType2_t));
	a2gs_DLL_AddNode(list, (int *) &x, sizeof(int));
	a2gs_DLL_AddNode(list, (char *) s, strlen(s));

	printf("Total inserted: [%ld]\n", a2gs_DLL_GetTotal(list));





	return(0);
}
