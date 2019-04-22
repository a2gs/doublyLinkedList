/* Andre Augusto Giannotti Scota
 * andre.scota@gmail.com
 *
 * A Doubly Linked List (DLL) sample
 *
 * MIT License
 *
 */


/* sample.c
 * A sample of Doubly Linked List lib
 *
 *
 *  Who     | When       | What
 *  --------+------------+----------------------------
 *   a2gs   | 22/05/2005 | Creation
 */


/* *** INCLUDES *** */
#include <stdio.h>
#include <string.h>
#include "liba2gs_doublyLinkedList.h"


/* *** DEFINES AND LOCAL DATA TYPE DEFINATION *** */
typedef struct _userType1_t{
	char a[10];
	int b;
}userType1_t;

typedef struct _userType2_t{
	char c[10];
	float d;
}userType2_t;

typedef enum{
	VAR1 = 1,
	VAR2,
	STR,
	INT,
	UNKNOW
}elementType_e;

typedef struct _genericElement_t{
	void *data;
	elementType_e type;
}genericElement_t;

/* *** LOCAL PROTOTYPES *** */


/* *** EXTERNS / LOCAL GLOBALS *** */


/* ------------------------------------------------------------------------------------------- */
void printAll(a2gs_DLL_Control_t *list)
{
	a2gs_DLL_Node_t *walker = NULL;
	unsigned int i = 0;

	for(walker = a2gs_DLL_Next(list), i = 0; walker != NULL; walker = a2gs_DLL_Next(list), i++){
		/* kkkk .... are you ready to C pointer-fu? */
		switch(((genericElement_t *)walker)->type){
			case VAR1:
				printf("\t%2d: Stored: [[%s][%d]]\n", i, ((userType1_t *)((genericElement_t *)walker)->data)->a, ((userType1_t *)((genericElement_t *)walker)->data)->b);
				break;
			case VAR2:
				printf("\t%2d: Stored: [[%s][%2.2f]]\n", i, ((userType2_t *)((genericElement_t *)walker)->data)->c, ((userType2_t *)((genericElement_t *)walker)->data)->d);
				break;
			case INT:
				printf("\t%2d: Stored: [%d]\n", i, (*(int *)((genericElement_t *)walker)->data));
				break;
			case STR:
				printf("\t%2d: Stored: [%s]\n", i, ((char *)((genericElement_t *)walker)->data));
				break;
			case UNKNOW:
				printf("\t%2d: Stored: [UNKNOW TYPE]\n", i);
				break;
		}
	}
	return;
}

int main(int argc, char *argv[])
{
	a2gs_DLL_Control_t *list = NULL;
	userType1_t var1 = {.a = "sample 1", .b = 81};
	userType2_t var2 = {.c = "sample 2", .d = 13.8};
	userType2_t var3 = {.c = "sample 3", .d = 3.14};
	userType2_t var4 = {.c = "sample 5", .d = 2.71};
	int x = 10;
	char *s = "sample 4";
	unsigned int i = 0;
	genericElement_t elements[] = {
		{.data = &var1, .type = VAR1},
		{.data = &var2, .type = VAR2},
		{.data = &x,    .type = INT},
		{.data = s,     .type = STR},
		{.data = &var3, .type = VAR2},
		{.data = &var4, .type = VAR1},
		{.data = NULL,  .type = UNKNOW}
	};

	/*
---int a2gs_DLL_Create(a2gs_DLL_Control_t **list);
---void a2gs_DLL_StartWalker(a2gs_DLL_Control_t *list);                                                                 
---void * a2gs_DLL_Next(a2gs_DLL_Control_t *list);

void * a2gs_DLL_Previous(a2gs_DLL_Control_t *list);

---int a2gs_DLL_AddNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize);

void * a2gs_DLL_GetLastValue(a2gs_DLL_Control_t *list);
int a2gs_DLL_RemoveNodeValue(a2gs_DLL_Control_t *list, a2gs_DLL_Node_t *node);
void * a2gs_DLL_GetCurrentNodeValue(a2gs_DLL_Control_t *list);
void * a2gs_DLL_GetValueFromThisNode(a2gs_DLL_Node_t *node);
a2gs_DLL_Node_t * a2gs_DLL_SearchNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize, unsigned int offset);

*int a2gs_DLL_DeleteTopValue(a2gs_DLL_Control_t *list);

---unsigned long a2gs_DLL_GetTotal(a2gs_DLL_Control_t *list);

*int a2gs_DLL_DeleteBottomValue(a2gs_DLL_Control_t *list);

---int a2gs_DLL_Delete(a2gs_DLL_Control_t *list);
---void a2gs_DLL_Destroy(a2gs_DLL_Control_t *list);
*/

	if(a2gs_DLL_Create(&list) == A2GS_DLL_ERRO){
		printf("Erro creating DLL.\n");
		return(-1);
	}

	/* ATTENTION:
	 * a2gs_DLL_AddNode() makes a COPY (memcpy()) of &e1. Inside e1 there is a pointer and this is what is copied (genericElement_t is
	 * a user-developer facility to identify yourself type. The lib supports list of any kind AND differents types inside the same list!),
	 * not the address where it points to (a void *, nao userType2_t and so on). Therefore var1, var2,..., x and s are 'staked' into main().
	 * genericElement_t had been created to help identify the data's type, but the DLL can be whole of the same (well know) type.
	 */

	printf("1) Inserting:\n");
	for(i = 0; elements[i].data != NULL; i++){
		printf("\t%d element...\n", i);
		if(a2gs_DLL_AddNode(list, &elements[i], sizeof(genericElement_t)) == A2GS_DLL_ERRO){
			printf("Erro adding a element %d: [%s] Error code: [%d].\n", i, A2GS_DLL_GET_ERRORMSG(list), A2GS_DLL_GET_ERRORCOD(list));
			return(-1);
		}
	}

	printf("\n* Total inserted: [%ld]\n\n", a2gs_DLL_GetTotal(list));

	printf("2) Listing:\n");

	a2gs_DLL_StartWalk(list);

	printAll(list);

	printf("\n3) Deleting the top element.\n\n");
	a2gs_DLL_DeleteTopValue(list);

	printf("4) Deleting the bottom element.\n\n");
	a2gs_DLL_DeleteBottomValue(list);
	printf("* Total remaining: [%ld]\n\n", a2gs_DLL_GetTotal(list));

	printf("5) Listing after deleting top and bottom elements:\n");

	a2gs_DLL_StartWalk(list);
	printAll(list);







	/*
	void * a2gs_DLL_Previous(a2gs_DLL_Control_t *list);
	void * a2gs_DLL_GetLastValue(a2gs_DLL_Control_t *list);
	int a2gs_DLL_RemoveNodeValue(a2gs_DLL_Control_t *list, a2gs_DLL_Node_t *node);
	void * a2gs_DLL_GetCurrentNodeValue(a2gs_DLL_Control_t *list);
	void * a2gs_DLL_GetValueFromThisNode(a2gs_DLL_Node_t *node);
	a2gs_DLL_Node_t * a2gs_DLL_SearchNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize, unsigned int offset);
	*/



	/* Deleting all elements */
	a2gs_DLL_Delete(list);

	/* Destroing the list */
	a2gs_DLL_Destroy(list);

	return(0);
}
