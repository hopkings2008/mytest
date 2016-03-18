#include <stdlib.h>

typedef struct QElem{
	struct QElem *next;
	struct QElem *prev;
	void *elem;
}QElem;

typedef struct Queue{
	QElem *head;
	QElem *tail;
	int count;
	int (*push)(struct Queue *q, void *elem);
	void * (*pop)(struct Queue *q);
	int (*size)(struct Queue *q);
}Queue;

Queue *QueueCreate();
