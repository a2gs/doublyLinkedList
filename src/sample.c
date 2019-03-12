
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
	float d;
}userType2_t;

/* TODO: It is a user-developer obligation (load every element into a struct from (pos fetched) which can be recognized)

typedef enum
{
	VAR1 = 1,
	VAR2,
	STR,
	INT
}elementType_e;

typedef struct _element_t{
	void *data;
	elementType_e type;
}element_t;

*/

/* *** LOCAL PROTOTYPES *** */


/* *** EXTERNS / LOCAL GLOBALS *** */


/* ------------------------------------------------------------------------------------------- */

int main(int argc, char *argv[])
{
	a2gs_DLL_Control_t *list = NULL;
	userType1_t var1 = {"sample 1", 81};
	userType2_t var2 = {"sample 2", 13.8};
	int x = 10;
	char *s = "sample 3";
	a2gs_DLL_Node_t *walker = NULL;
	unsigned int i = 0; /* Workaround. See TODO above */

	/*
---int a2gs_DLL_Create(a2gs_DLL_Control_t **list);
---void a2gs_DLL_StartFetch(a2gs_DLL_Control_t *list);                                                                 
---void * a2gs_DLL_Fetch(a2gs_DLL_Control_t *list);
void * a2gs_DLL_Previous(a2gs_DLL_Control_t *list);
---int a2gs_DLL_AddNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize);
void * a2gs_DLL_GetLastValue(a2gs_DLL_Control_t *list);
int a2gs_DLL_RemoveNodeValue(a2gs_DLL_Control_t *list, a2gs_DLL_Node_t *node);
void * a2gs_DLL_GetCurrentNodeValue(a2gs_DLL_Control_t *list);
void * a2gs_DLL_GetValueFromThisNode(a2gs_DLL_Node_t *node);
a2gs_DLL_Node_t * a2gs_DLL_SearchNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize, unsigned int offset);
int a2gs_DLL_DeleteTopValue(a2gs_DLL_Control_t *list);
---unsigned long a2gs_DLL_GetTotal(a2gs_DLL_Control_t *list);
int a2gs_DLL_DeleteBottomValue(a2gs_DLL_Control_t *list);
---int a2gs_DLL_Delete(a2gs_DLL_Control_t *list);
---void a2gs_DLL_Destroy(a2gs_DLL_Control_t *list);
*/


	if(a2gs_DLL_Create(&list) == A2GS_DLL_ERRO){
		printf("Erro creating DLL.\n");
		return(-1);
	}

	if(a2gs_DLL_AddNode(list, (userType1_t *) &var1, sizeof(userType1_t)) == A2GS_DLL_ERRO){
		printf("Erro adding a element 1: [%s] Error code: [%d].\n", A2GS_DLL_GET_ERRORMSG(list), A2GS_DLL_GET_ERRORCOD(list));
		return(-1);
	}

	if(a2gs_DLL_AddNode(list, (userType2_t *) &var2, sizeof(userType2_t)) == A2GS_DLL_ERRO){
		printf("Erro adding a element 2: [%s] Error code: [%d].\n", A2GS_DLL_GET_ERRORMSG(list), A2GS_DLL_GET_ERRORCOD(list));
		return(-1);
	}

	if(a2gs_DLL_AddNode(list, (int *) &x, sizeof(int)) == A2GS_DLL_ERRO){
		printf("Erro adding a element 3: [%s] Error code: [%d].\n", A2GS_DLL_GET_ERRORMSG(list), A2GS_DLL_GET_ERRORCOD(list));
		return(-1);
	}

	if(a2gs_DLL_AddNode(list, (char *) s, strlen((const char *)s)) == A2GS_DLL_ERRO){
		printf("Erro adding a element 4: [%s] Error code: [%d].\n", A2GS_DLL_GET_ERRORMSG(list), A2GS_DLL_GET_ERRORCOD(list));
		return(-1);
	}

	printf("Total inserted: [%ld]\n", a2gs_DLL_GetTotal(list));

	printf("Listing:\n");

	a2gs_DLL_StartFetch(list);

	for(walker = a2gs_DLL_Fetch(list), i = 0; walker != NULL; walker = a2gs_DLL_Fetch(list), i++){
		switch(i){ /* See TODO above, it is just a workaround to define the data type stored */
			case 0:
				printf("%02d: Stored: [[%s][%d]]\n", i+1, ((userType1_t *)walker)->a, ((userType1_t *)walker)->b);
				break;
			case 1:
				printf("%02d: Stored: [[%s][%2.1f]]\n", i+1, ((userType2_t *)walker)->c, ((userType2_t *)walker)->d);
				break;
			case 2:
				printf("%02d: Stored: [%d]\n", i+1, *((int *)walker));
				break;
			case 3:
				printf("%02d: Stored: [%s]\n", i+1, (char *)walker);
				break;
		}
	}



	/* Deleting all elements */
	a2gs_DLL_Delete(list);

	/* Destroing the list */
	a2gs_DLL_Destroy(list);

	return(0);
}
