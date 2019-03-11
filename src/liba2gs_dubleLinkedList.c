/* Andre Augusto Giannotti Scota
 * andre.scota@gmail.com
 *
 * A Duble Linked List API
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "dubleLinkedList.h"


/* *** DEFINES AND LOCAL DATA TYPE DEFINATION *** */
#define A2GS_LINKEDLIST_CLEAN_ERRO(__list_){                                       \
                                            (__list_)->erro = a2gs_LinkedList_EOk; \
                                            (__list_)->erroMsg[0] = '\0';          \
	                                        }
#define A2GS_LINKEDLIST_SET_ERRO(__list_, __erro_, __erroMsg_){                                                                        \
                                                                (__list_)->erro = __erro_;                                             \
                                                                strncpy((__list_)->erroMsg, __erroMsg_, A2GS_LINKEDLIST_ERROMSG_SIZE); \
	                                                           }


/* *** LOCAL PROTOTYPES *** */


/* *** EXTERNS / LOCAL GLOBALS *** */


/* ------------------------------------------------------------------------------------------- */

/* int a2gs_LinkedList_CreateLinkedList(a2gs_LinkedList_Control_t **list)
 *
 * Cria/Inicializa uma lista encadeada.
 *
 * INPUT:
 *  list     - Ponteiro de ponteiro para uma struct de controle de uma lista criada
 * OUTPUT:
 *  list     - Ponteiro de ponteiro para uma struct de controle de uma lista criada, ou NULL caso de erro
 *  A2GS_LINKEDLIST_OK   - Criacao Ok
 *  A2GS_LINKEDLIST_ERRO - Erro na criacao
 */
int a2gs_LinkedList_Create(a2gs_LinkedList_Control_t **list)
{
	if((*list = (a2gs_LinkedList_Control_t *)malloc(sizeof(a2gs_LinkedList_Control_t))) == NULL){
		(*list) = NULL;
		return(A2GS_LINKEDLIST_ERRO);
	}

	memset(*list, 0, sizeof(a2gs_LinkedList_Control_t));

	(*list)->start = NULL;
	(*list)->end = NULL;
	(*list)->now = NULL;
	(*list)->total = 0;

	A2GS_LINKEDLIST_CLEAN_ERRO(*list)

	return(A2GS_LINKEDLIST_OK);
}


/* void * a2gs_LinkedList_FetchLinkedList(a2gs_LinkedList_Control_t *list)
 *
 * Retorna o valor apontado pelo ponteiro de 'fetching' de uma determinada lista.
 *
 * INPUT:
 *  list - Ponteiro para uma struct de controle de uma lista criada
 * OUTPUT:
 *  Endereco do valor apontado
 */

void * a2gs_LinkedList_Fetch(a2gs_LinkedList_Control_t *list)
{
	void *value = NULL;

	A2GS_LINKEDLIST_CLEAN_ERRO(list);

	if(list->now != NULL){
		value = list->now->value;
		list->now = list->now->next;
	}else{
		A2GS_LINKEDLIST_SET_ERRO(list, a2gs_LinkedList_ENoMoreNodes, A2GS_LINKEDLIST_MSG2);
		value = NULL;
	}

	return(value);
}


/* void a2gs_LinkedList_StartFetchLinkedList(a2gs_LinkedList_Control_t *list)
 *
 * Inicializa o fetch para inicio da lista.
 *
 * INPUT:
 *  list - Ponteiro para uma struct de controle de uma lista criada
 * OUTPUT:
 *  Nenhum
 */
void a2gs_LinkedList_StartFetch(a2gs_LinkedList_Control_t *list)
{
	A2GS_LINKEDLIST_CLEAN_ERRO(list);

	list->now = list->start;
	return;
}


/* int a2gs_LinkedList_AddNodeLinkedList(a2gs_LinkedList_Control_t *list, void *value, size_t valueSize)
 *
 * Adiciona um node em uma determinada lista encadeada.
 *
 * INPUT:
 *  list      - Ponteiro para uma struct de controle de uma lista
 *  value     - Valor a ser procurado
 *  valueSize - Tamanho do dado que aponta value
 * OUTPUT:
 *  A2GS_LINKEDLIST_OK    - Insercao Ok
 *  A2GS_LINKEDLIST_ERRO  - Erro na insercao
 */
int a2gs_LinkedList_AddNode(a2gs_LinkedList_Control_t *list, void *value, size_t valueSize)
{
	a2gs_LinkedList_Node_t *node = NULL;

	A2GS_LINKEDLIST_CLEAN_ERRO(list);

	if((node = (a2gs_LinkedList_Node_t *)malloc(sizeof(a2gs_LinkedList_Node_t))) == NULL){
		char erroMsgAux[A2GS_LINKEDLIST_ERROMSG_SIZE + 1] = {0};

		snprintf(erroMsgAux, A2GS_LINKEDLIST_ERROMSG_SIZE, A2GS_LINKEDLIST_MSG1, strerror(errno));
		A2GS_LINKEDLIST_SET_ERRO(list, a2gs_LinkedList_EAllocMemory, erroMsgAux);
		return(A2GS_LINKEDLIST_ERRO);
	}

	/* we take a value copy */
	if((node->value = malloc(valueSize)) == NULL){
		char erroMsgAux[A2GS_LINKEDLIST_ERROMSG_SIZE + 1] = {0};

		snprintf(erroMsgAux, A2GS_LINKEDLIST_ERROMSG_SIZE, A2GS_LINKEDLIST_MSG3, strerror(errno));
		A2GS_LINKEDLIST_SET_ERRO(list, a2gs_LinkedList_EAllocMemory, erroMsgAux);
		return(A2GS_LINKEDLIST_ERRO);
	}

	memcpy(node->value, value, valueSize);

	node->next = NULL;
	node->prev = list->end;

	if(list->start == NULL)
		list->start = node;

	if(list->end != NULL)
		list->end->next = node;

	list->end = node;

	list->total++;

	return(A2GS_LINKEDLIST_OK);
}


/* void * a2gs_LinkedList_GetLastValueLinkedList(a2gs_LinkedList_Control_t *list)
 *
 * Retorna o valor do ultimo node.
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 * OUTPUT:
 *  Retorna ponteiro para o valor do ultimo node ou NULL caso nao exista nenhum
 */
void * a2gs_LinkedList_GetLastValue(a2gs_LinkedList_Control_t *list)
{
	A2GS_LINKEDLIST_CLEAN_ERRO(list);
	return(list->end->value);
}


/* int a2gs_LinkedList_RemoveNodeValueLinkedList(a2gs_LinkedList_Control_t *list, a2gs_LinkedList_Node_t *node)
 *
 * Remove um node e o valor associado em uma determinada lista encadeada.
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 *  node     - Node a ser removido
 * OUTPUT:
 *  A2GS_LINKEDLIST_OK   - Valor achado e removido
 *  A2GS_LINKEDLIST_ERRO - Valor nao localizado
 */
int a2gs_LinkedList_RemoveNodeValue(a2gs_LinkedList_Control_t *list, a2gs_LinkedList_Node_t *node)
{
	A2GS_LINKEDLIST_CLEAN_ERRO(list);

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
		A2GS_LINKEDLIST_SET_ERRO(list, a2gs_LinkedList_EUnknowNode, A2GS_LINKEDLIST_MSG4);
		return(A2GS_LINKEDLIST_ERRO);
	}

	free(node->value);
	free(node);

	list->total--;

	return(A2GS_LINKEDLIST_OK);
}

void * a2gs_LinkedList_GetCurrentNodeValure(a2gs_LinkedList_Control_t *list)
{
	A2GS_LINKEDLIST_CLEAN_ERRO(list);

	return(list->now->value);
}

void * a2gs_LinkedList_GetValueFromThisNode(a2gs_LinkedList_Node_t *node){
	return(node->value);
}

/* TODO begin */
/* a2gs_LinkedList_Node_t * a2gs_LinkedList_SearchNodeLinkedList(a2gs_LinkedList_Control_t *list, void *value, size_t valueSize)
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

a2gs_LinkedList_Node_t * a2gs_LinkedList_SearchNode(a2gs_LinkedList_Control_t *list, void *value, int compare(void *, void *))

>>>>>>>>>>>>>>>>>>>>> USAR offsetof() em stderr.h !!!!!!! <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

a2gs_LinkedList_Node_t * a2gs_LinkedList_SearchNode(a2gs_LinkedList_Control_t *list, void *value, size_t valueSize, unsigned int offset)
{
	a2gs_LinkedList_Node_t *node = NULL;

	A2GS_LINKEDLIST_CLEAN_ERRO(list);

	for(node = list->start; node != NULL; node = node->next){
		if(memcmp(value, ((char *)(node->value))+offset, valueSize) == 0)
			return(node);
	}

	return(NULL);
}
/* TODO end */


/* int a2gs_LinkedList_DeleteTopValueLinkedList(a2gs_LinkedList_Control_t *list)
 *
 * Remove da memoria o node do topo da lista.
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 * OUTPUT:
 *  A2GS_LINKEDLIST_OK   - Delecao Ok
 *  A2GS_LINKEDLIST_ERRO - Erro na delecao
 */
int a2gs_LinkedList_DeleteTopValue(a2gs_LinkedList_Control_t *list)
{
	a2gs_LinkedList_Node_t *node = NULL;

	A2GS_LINKEDLIST_CLEAN_ERRO(list);

	node = list->start;

	if(node == NULL){
		A2GS_LINKEDLIST_SET_ERRO(list, a2gs_LinkedList_ENoMoreNodes, A2GS_LINKEDLIST_MSG5);
		return(A2GS_LINKEDLIST_ERRO);
	}

	if(node->next == NULL){
		list->start = NULL; /* It was the only one node */
		list->end = NULL;
	}else
		list->start = node->next;

	list->total--;

	free(node->value);
	free(node);

	return(A2GS_LINKEDLIST_OK);
}


/* unsigned long a2gs_LinkedList_GetTotal(a2gs_LinkedList_Control_t *list){
 *
 * Retorna o total de elementos.
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 * OUTPUT:
 *  A2GS_LINKEDLIST_OK   -
 *  A2GS_LINKEDLIST_ERRO -
 */
unsigned long a2gs_LinkedList_GetTotal(a2gs_LinkedList_Control_t *list){
	A2GS_LINKEDLIST_CLEAN_ERRO(list);

	return(list->total);
}


/* int a2gs_LinkedList_DeleteBottomValueLinkedList(a2gs_LinkedList_Control_t *list)
 *
 * Remove da memoria o node do fim da lista.
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 * OUTPUT:
 *  A2GS_LINKEDLIST_OK   - Delecao Ok
 *  A2GS_LINKEDLIST_ERRO - Erro na delecao
 */
int a2gs_LinkedList_DeleteBottomValue(a2gs_LinkedList_Control_t *list)
{
	a2gs_LinkedList_Node_t *node = NULL;

	A2GS_LINKEDLIST_CLEAN_ERRO(list);

	node = list->end;

	if(node == NULL){
		A2GS_LINKEDLIST_SET_ERRO(list, a2gs_LinkedList_ENoMoreNodes, A2GS_LINKEDLIST_MSG5);
		return(A2GS_LINKEDLIST_ERRO);
	}

	if(node->prev == NULL){
		list->start = NULL; /* It was the only one node */
		list->end = NULL;
	}else
		list->end = node->prev;

	list->total--;

	free(node->value);
	free(node);
	return(A2GS_LINKEDLIST_OK);
}


/* int a2gs_LinkedList_DeleteLinkedList(a2gs_LinkedList_Control_t *list)
 *
 * Remove da memoria todos os nodes e a struct de controle de uma determinada lista encadeada.
 * (Deixa a lista vazia)
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 * OUTPUT:
 *  A2GS_LINKEDLIST_OK   - Delecao Ok
 *  A2GS_LINKEDLIST_ERRO - Erro na delecao
 */
int a2gs_LinkedList_Delete(a2gs_LinkedList_Control_t *list)
{
	a2gs_LinkedList_Node_t *node = NULL, *nextSaved = NULL;

	A2GS_LINKEDLIST_CLEAN_ERRO(list);

	for(node = nextSaved = list->start; nextSaved != NULL; node = nextSaved){
		nextSaved = node->next;
		free(node->value);
		free(node);
	}

	list->start = list->end = NULL;
	list->total = 0;

	return(A2GS_LINKEDLIST_OK);
}


/* void a2gs_LinkedList_DestroyLinkedList(a2gs_LinkedList_Control_t *list)
 *
 * Remove da memoria a estrutura de controle de uma lista.
 *
 * INPUT:
 *  list     - Ponteiro para uma struct de controle de uma lista
 * OUTPUT:
 *  Nenhum
 */
void a2gs_LinkedList_Destroy(a2gs_LinkedList_Control_t *list)
{
	A2GS_LINKEDLIST_CLEAN_ERRO(list);

	free(list);
	return;
}


/* TODO: SAMPLE USAGE */
int main(int argc, char *argv[])
{

	printf("TODO: a API sample usage\n");

	return(0);
}
