#include <stdio.h>
#include <stdlib.h>
#include "header/queue.h"

void create(QUEUE *queue);
int offer(ITEM item, QUEUE *queue);
int poll(QUEUE *queue, ITEM *item);
int empty(QUEUE *queue);

int main(){

	QUEUE queue;
	create(&queue);

	ITEM item;
	item.key = 99;
	offer(item,&queue);

	ITEM item2;
	item2.key = 3;
	offer(item2,&queue);

	ITEM itemPrint;

	poll(&queue, &itemPrint);
	printf("%d\n", itemPrint.key);

	poll(&queue, &itemPrint);
	printf("%d\n", itemPrint.key);

	printf("\n\nPress ENTER key to Continue\n");
	getchar();

	return 0;
}

void create(QUEUE *queue) {
	queue->first = (PONT)malloc(sizeof(CELL));
	queue->last = queue->first;
	queue->first->next = NULL;
}


int offer(ITEM item, QUEUE *queue) {
	queue->last->next = (PONT)malloc(sizeof(CELL));
	queue->last = queue->last->next;
	queue->last->item = item;
	queue->last->next = NULL;

	return 0;
}

int poll(QUEUE *queue, ITEM *item) {
	if (queue->first->next == NULL)
		return -1;

	*item = queue->first->next->item;
	queue->first = queue->first->next;

	return 0;
}

int empty(QUEUE *queue) {
	return queue->first == queue->last ? 0 : -1;
}