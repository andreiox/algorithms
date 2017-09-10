#if !defined (QUEUE_H)
#define QUEUE_H

typedef struct CELL_TAG *PONT;

typedef struct {
	int key;
} ITEM;

typedef struct CELL_TAG {
	ITEM item;
	PONT next;
} CELL;

typedef struct {
	PONT first, last;
} QUEUE;

void create (QUEUE*);
int empty (QUEUE*);
int offer (ITEM, QUEUE*);
int poll (QUEUE*, ITEM*);

#endif
