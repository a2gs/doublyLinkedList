/* Andre Augusto Giannotti Scota
 * andre.scota@gmail.com
 *
 * A Doubly Linked List (DLL) API
 *
 * MIT License
 *
 */


/* doublyLinkedList.c
 * A Doubly Linked List implementation
 *
 *
 *  Who     | When       | What
 *  --------+------------+----------------------------
 *   a2gs   | 22/05/2005 | Creation
 */


/* *** INCLUDES *** */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "liba2gs_doublyLinkedList.h"


/* *** DEFINES AND LOCAL DATA TYPE DEFINATION *** */
#define A2GS_DLL_CLEAN_ERRO(__list_){                                \
                                     (__list_)->erro = a2gs_DLL_EOk; \
                                     (__list_)->erroMsg[0] = '\0';   \
	                            }
#define A2GS_DLL_SET_ERRO(__list_, __erro_, __erroMsg_){                                                                \
                                                        (__list_)->erro = __erro_;                                      \
                                                        strncpy((__list_)->erroMsg, __erroMsg_, A2GS_DLL_ERROMSG_SIZE); \
	                                               }


/* *** LOCAL PROTOTYPES *** */


/* *** EXTERNS / LOCAL GLOBALS *** */


/* ------------------------------------------------------------------------------------------- */

/* int a2gs_DLL_CreateDLL(a2gs_DLL_Control_t **list)
 *
 * Cria/Inicializa uma lista encadeada.
 *
 * INPUT:
 *  list     - Ponteiro de ponteiro para uma struct de controle de uma lista criada
 * OUTPUT:
 *  list     - Ponteiro de ponteiro para uma struct de controle de uma lista criada, ou NULL caso de erro
 *  A2GS_DLL_OK   - Criacao Ok
 *  A2GS_DLL_ERRO - Erro na criacao
 */
int a2gs_DLL_Create(a2gs_DLL_Control_t **list)
{
	if((*list = (a2gs_DLL_Control_t *)malloc(sizeof(a2gs_DLL_Control_t))) == NULL){
		(*list) = NULL;
		return(A2GS_DLL_ERRO);
	}

	memset(*list, 0, sizeof(a2gs_DLL_Control_t));

	(*list)->start = NULL;
	(*list)->end = NULL;
	(*list)->now = NULL;
	(*list)->total = 0;

	A2GS_DLL_CLEAN_ERRO(*list)

	return(A2GS_DLL_OK);
}

/* TODO: return the element previous after last next */
void * a2gs_DLL_Previous(a2gs_DLL_Control_t *list)
{
	return((void *)list);
}

/* void * a2gs_DLL_Next(a2gs_DLL_Control_t *list)
 *
 * Retorna o valor apontado pelo ponteiro de 'fetching' de uma determinada lista.
 *
 * INPUT:
 *  list - Ponteiro para uma struct de controle de uma lista criada
 * OUTPUT:
 *  Endereco do valor apontado
 */
void * a2gs_DLL_Next(a2gs_DLL_Control_t *list)
{
	void *value = NULL;

	A2GS_DLL_CLEAN_ERRO(list);

	if(list->now != NULL){
		value = list->now->value;
		list->now = list->now->next;
	}else{
		A2GS_DLL_SET_ERRO(list, a2gs_DLL_ENoMoreNodes, A2GS_DLL_MSG2);
		value = NULL;
	}

	return(value);
}


/* void a2gs_DLL_StartWalk(a2gs_DLL_Control_t *list)
 *
 * Inicializa o next/previous para inicio da lista.
 *
 * INPUT:
 *  list - Ponteiro para uma struct de controle de uma lista criada
 * OUTPUT:
 *  Nenhum
 */
void a2gs_DLL_StartWalk(a2gs_DLL_Control_t *list)
{
	A2GS_DLL_CLEAN_ERRO(list);

	list->now = list->start;
	return;
}


/* int a2gs_DLL_AddNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize)
 *
 * Adiciona um node em uma determinada lista encadeada.
 *
 * INPUT:
 *  list      - Ponteiro para uma struct de controle de uma lista
 *  value     - Valor a ser procurado
 *  valueSize - Tamanho do dado que aponta value
 * OUTPUT:
 *  A2GS_DLL_OK    - Insercao Ok
 *  A2GS_DLL_ERRO  - Erro na insercao
 */
int a2gs_DLL_AddNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize)
{
	a2gs_DLL_Node_t *node = NULL;

	A2GS_DLL_CLEAN_ERRO(list);

	if((node = (a2gs_DLL_Node_t *)malloc(sizeof(a2gs_DLL_Node_t))) == NULL){
		char erroMsgAux[A2GS_DLL_ERROMSG_SIZE + 1] = {0};

		snprintf(erroMsgAux, A2GS_DLL_ERROMSG_SIZE, A2GS_DLL_MSG1, strerror(errno));
		A2GS_DLL_SET_ERRO(list, a2gs_DLL_EAllocMemory, erroMsgAux);
		return(A2GS_DLL_ERRO);
	}
	memset(node, 0, sizeof(a2gs_DLL_Node_t));

	/* we take a value copy */
	if((node->value = malloc(valueSize)) == NULL){
		char erroMsgAux[A2GS_DLL_ERROMSG_SIZE + 1] = {0};

		snprintf(erroMsgAux, A2GS_DLL_ERROMSG_SIZE, A2GS_DLL_MSG3, strerror(errno));
		A2GS_DLL_SET_ERRO(list, a2gs_DLL_EAllocMemory, erroMsgAux);
		return(A2GS_DLL_ERRO);
	}

	memcpy(node->value, (const void *) value, valueSize);

	node->next = NULL;
	node->prev = list->end;

	if(list->start == NULL)
		list->start = node;

	if(list->end != NULL)
		list->end->next = node;

	list->end = node;

	list->total++;

	return(A2GS_DLL_OK);
}


/* void * a2gs_DLL_GetLastValue(a2gs_DLL_Control_t *list)
 *
 * Retorna o valor do ultimo node.
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 * OUTPUT:
 *  Retorna ponteiro para o valor do ultimo node ou NULL caso nao exista nenhum
 */
void * a2gs_DLL_GetLastValue(a2gs_DLL_Control_t *list)
{
	A2GS_DLL_CLEAN_ERRO(list);
	return(list->end->value);
}


/* int a2gs_DLL_RemoveNodeValue(a2gs_DLL_Control_t *list, a2gs_DLL_Node_t *node)
 *
 * Remove um node e o valor associado em uma determinada lista encadeada.
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 *  node     - Node a ser removido
 * OUTPUT:
 *  A2GS_DLL_OK   - Valor achado e removido
 *  A2GS_DLL_ERRO - Valor nao localizado
 */
int a2gs_DLL_RemoveNodeValue(a2gs_DLL_Control_t *list, a2gs_DLL_Node_t *node)
{
	A2GS_DLL_CLEAN_ERRO(list);

	if((node == list->start) && (node == list->end)){
		/* It is a alone node */
		list->start = list->end = NULL;
	}else if((node == list->start) && (node != list->end)){
		/* It is the first, but has more nodes */
		list->start = node->next;
		node->next->prev = NULL;
	}else if((node != list->start) && (node == list->end)){
		/* It is the last node, but there are more */
		list->end = node->prev;
		node->prev->next= NULL;
	}else if((node != list->start) && (node != list->end)){
		/* There are nodes before and after it */
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}else{
		A2GS_DLL_SET_ERRO(list, a2gs_DLL_EUnknowNode, A2GS_DLL_MSG4);
		return(A2GS_DLL_ERRO);
	}

	free(node->value);
	free(node);

	list->total--;

	return(A2GS_DLL_OK);
}

void * a2gs_DLL_GetCurrentNodeValue(a2gs_DLL_Control_t *list)
{
	A2GS_DLL_CLEAN_ERRO(list);

	return(list->now->value);
}

void * a2gs_DLL_GetValueFromThisNode(a2gs_DLL_Node_t *node)
{
	return(node->value);
}

/* TODO begin */
/* a2gs_DLL_Node_t * a2gs_DLL_SearchNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize)
 *
 * Procura um node em uma determinada lista encadeada.
 *
 * INPUT:
 *  list      - Ponteiro para uma struct de controle de uma lista
 *  value     - Valor a ser removido da lista
 *  valueSize - Quantidade de bytes que ira comparar iniciando de value + offset
 *  offset    - Distancia para iniciar a comparacao a partir de onde aponta value. Uso com offsetof() de stddef.h
 * OUTPUT:
 *            - Aponta para o valor procurado ou NULL em caso nao for localizado
 */
/* TODO
int compare(x,y){
	y==x
		1;
	else
		0;
}

a2gs_DLL_Node_t * a2gs_DLL_SearchNode(a2gs_DLL_Control_t *list, void *value, int compare(void *, void *))

>>>>>>>>>>>>>>>>>>>>> USAR offsetof() em stderr.h !!!!!!! <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

a2gs_DLL_Node_t * a2gs_DLL_SearchNode(a2gs_DLL_Control_t *list, void *value, size_t valueSize, unsigned int offset)
{
	a2gs_DLL_Node_t *node = NULL;

	A2GS_DLL_CLEAN_ERRO(list);

	for(node = list->start; node != NULL; node = node->next){
		if(memcmp(value, ((char *)(node->value))+offset, valueSize) == 0)
			return(node);
	}

	return(NULL);
}
/* TODO end */


/* int a2gs_DLL_DeleteTopValue(a2gs_DLL_Control_t *list)
 *
 * Remove da memoria o node do topo da lista.
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 * OUTPUT:
 *  A2GS_DLL_OK   - Delecao Ok
 *  A2GS_DLL_ERRO - Erro na delecao
 */
int a2gs_DLL_DeleteTopValue(a2gs_DLL_Control_t *list)
{
	a2gs_DLL_Node_t *node = NULL;

	A2GS_DLL_CLEAN_ERRO(list);

	node = list->start;

	if(node == NULL){
		A2GS_DLL_SET_ERRO(list, a2gs_DLL_ENoMoreNodes, A2GS_DLL_MSG5);
		return(A2GS_DLL_ERRO);
	}

	if(node->next == NULL){
		list->start = NULL; /* It was the only one node */
		list->end = NULL;
	}else
		list->start = node->next;

	list->total--;

	free(node->value);
	free(node);

	return(A2GS_DLL_OK);
}


/* unsigned long a2gs_DLL_GetTotal(a2gs_DLL_Control_t *list){
 *
 * Retorna o total de elementos.
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 * OUTPUT:
 *  A2GS_DLL_OK   -
 *  A2GS_DLL_ERRO -
 */
unsigned long a2gs_DLL_GetTotal(a2gs_DLL_Control_t *list){
	A2GS_DLL_CLEAN_ERRO(list);

	return(list->total);
}


/* int a2gs_DLL_DeleteBottomValue(a2gs_DLL_Control_t *list)
 *
 * Remove da memoria o node do fim da lista.
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 * OUTPUT:
 *  A2GS_DLL_OK   - Delecao Ok
 *  A2GS_DLL_ERRO - Erro na delecao
 */
int a2gs_DLL_DeleteBottomValue(a2gs_DLL_Control_t *list)
{
	a2gs_DLL_Node_t *node = NULL;

	A2GS_DLL_CLEAN_ERRO(list);

	node = list->end;

	if(node == NULL){
		A2GS_DLL_SET_ERRO(list, a2gs_DLL_ENoMoreNodes, A2GS_DLL_MSG5);
		return(A2GS_DLL_ERRO);
	}

	if(node->prev == NULL){
		list->start = NULL; /* It was the only one node */
		list->end = NULL;
	}else
		list->end = node->prev;

	list->total--;

	free(node->value);
	free(node);

	return(A2GS_DLL_OK);
}


/* int a2gs_DLL_Delete(a2gs_DLL_Control_t *list)
 *
 * Remove da memoria todos os nodes e a struct de controle de uma determinada lista encadeada.
 * (Deixa a lista vazia)
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 * OUTPUT:
 *  A2GS_DLL_OK   - Delecao Ok
 *  A2GS_DLL_ERRO - Erro na delecao
 */
int a2gs_DLL_Delete(a2gs_DLL_Control_t *list)
{
	a2gs_DLL_Node_t *node = NULL, *nextSaved = NULL;

	A2GS_DLL_CLEAN_ERRO(list);

	for(node = nextSaved = list->start; nextSaved != NULL; node = nextSaved){
		nextSaved = node->next;
		free(node->value);
		free(node);
	}

	list->start = list->end = NULL;
	list->total = 0;

	return(A2GS_DLL_OK);
}


/* void a2gs_DLL_Destroy(a2gs_DLL_Control_t *list)
 *
 * Remove da memoria a estrutura de controle de uma lista.
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 * OUTPUT:
 *  Nenhum
 */
void a2gs_DLL_Destroy(a2gs_DLL_Control_t *list)
{
	A2GS_DLL_CLEAN_ERRO(list);

	free(list);
	return;
}
