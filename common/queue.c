#include "queue.h"

static int push(Queue *q, void *elem){
	if(!q){
		return -1;
	}

	if(0 == q->count){
		q->head = q->tail = (Queue *)malloc(sizeof(Queue));
		q->head->next = 0;
		q->head->prev = 0;
		q->head->elem = elem;
		++q->count;
		return 0;
	}

	q->tail->next=(Queue *)malloc(sizeof(Queue));
	q->tail->next->next = 0;
	q->tail->next->prev = q->tail;
	q->tail->next->elem = elem;
	q->tail = q->tail->next;
	++q->count;

	return 0;
}

static void *pop(Queue *q){
	QElem *elem = (!q || 0 == q->count) ? 0 : q->head;
	if(!elem)
		return 0;
	if(q->head->next)
		q->head->next->prev = 0;
	q->head = q->head->next;
	elem->prev = 0;
	elem->next = 0;
	--q->count;
	return elem;
}

static int size(Queue *q) {
	return q->count;
}


Queue *QueueCreate(){
	Queue *q = (Queue *)malloc(sizeof(Queue));
	memset((char*)q, 0, sizeof(Queue));
	q->push = &push;
	q->pop = &pop;
	q->size = &size;
	return q;
}


