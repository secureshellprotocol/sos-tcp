#include <stddef.h>

typedef struct node_s 
	node_t;
typedef struct list_s 
	list_t;

list_t *list_alloc(void);

void list_free(list_t *list, void (*free_data)(void *data));

int list_prepend(list_t *list, void *val);

int list_append(list_t *list, void *val);

int list_insert(list_t *list, void *val, size_t pos);

int list_rm(list_t *list, void **val, size_t pos);

int list_set(list_t *list, void *val, size_t pos);

int list_get(list_t *list, void **val, size_t pos);
