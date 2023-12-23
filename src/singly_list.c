#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node_s {
	void			*data;
	struct node_s 	*next;
} node_t;
typedef struct list_s {
	node_t *head;
	node_t *tail;
	size_t size;
} SinglyList;

// functions to implement
SinglyList *list_alloc(void){
	SinglyList *l = (struct list_s *) malloc(sizeof(struct list_s));

	l->head = l->tail = NULL;
	l->size = 0;

	return l;
}

//insert at pos 0
int list_prepend(SinglyList *list, void* val){
	if(list == NULL) { return -1; }

	node_t *n = calloc(1, sizeof(struct node_s));
	
	//	empty list
	if(list->size == 0){
		list->tail = n;
	}

	n->next = list->head;
	list->head = n;
	list->size++;

	n->data = val;

	return 0;
}

//insert at pos head, size-1
int list_append(SinglyList *list, void *val){
	if(list == NULL) { return -1; }

	node_t *n = calloc(1, sizeof(struct node_s));
	
	//	empty list
	if(list->size == 0){
		list->head = n;
	}

	list->tail->next = n;
	list->tail = n;
	list->size++;

	n->data = val;

	return 0;
}

int list_insert(SinglyList *list, void* val, size_t pos){
	if(pos < 0 || pos > list->size-1 || list == NULL) { return -1; }

	if(pos == list->size-1){ //append
		return list_append(list, val);	
	}
	
	if(pos == 0){ //prepend
		return list_prepend(list, val);
	}

	node_t *n = calloc(1, sizeof(struct node_s));
	n->next = list->head; //start at 0

	for(int i = 0; i < pos-1; i++){
		n->next = n->next->next;
	}
	
	node_t *b = n->next;
	b->next = n;
	n->next = n->next->next;

	list->size++;

	n->data = val;

	return 0;
}

int list_set(SinglyList *list, void *val, size_t pos){
	if(pos < 0 || pos > list->size-1 || list == NULL) { return -1; }

	node_t *n = calloc(1, sizeof(struct node_s));
	n->next = list->head; //start at 0

	//march to pos
	for(int i = 0; i < pos; i++){
		n->next = n->next->next;
	}

	n->data = val;

	return 0;
}

int list_get(SinglyList *list, void *val, size_t pos){
	if(pos < 0 || pos > list->size-1 || list == NULL) { return -1; }

	node_t *n = calloc(1, sizeof(struct node_s));
	n->next = list->head; //start at 0

	for(int i = 0; i < pos; i++){
		n->next = n->next->next;
	}

	val = n->data;

	return 0;
}

int list_rm(SinglyList *list, void *val, size_t pos){
	if(pos < 0 || pos > list->size-1 || list == NULL) { return -1; }

	node_t *n = list->head; //start at 0

	for(int i = 0; i < pos-1; i++){
		n->next = n->next->next;
	}

	val = n->next->data;

	node_t *scourge = n->next;

	n->next = n->next->next;

	free(scourge);
	list->size--;

	return 0;
}

void list_free(SinglyList *list){
	if(list == NULL) { return; }

	node_t *n;

	while(list->head != NULL){
		n = list->head;
		list->head = list->head->next;
		free(n);
	}
	
	free(list);
	return;
}
