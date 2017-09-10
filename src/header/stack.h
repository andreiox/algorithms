#if !defined(STACK_H)
#define STACK_H

typedef struct CELL_TAG *PONT;

typedef struct {
	char key;
} ITEM;

typedef struct CELL_TAG {
	ITEM item;
	PONT next;
} CELL;

typedef struct{
	PONT bottom,top;
	int size;
} STACK;

void create (STACK*);
int empty (STACK);
int push (ITEM, STACK*);
int pop (ITEM*, STACK*);
char peek (STACK*);
int size (STACK);

#endif
