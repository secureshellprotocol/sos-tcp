#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node_s 
	node_t;
typedef struct list_s
	SinglyList;

SinglyList *list_alloc(void);

int list_prepend(SinglyList *list, void *val);

int list_append(SinglyList *list, void *val);

int list_insert(SinglyList *list, void *val, size_t pos);

int list_set(SinglyList *list, void *val, size_t pos);

int list_get(SinglyList *list, void *val, size_t pos);

int list_rm(SinglyList *list, void *val, size_t pos);

void list_free(SinglyList *list);
