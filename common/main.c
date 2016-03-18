#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

int main(int argc, char *argv[]){
	Queue *q = QueueCreate();
	QElem *e = 0;
	for(int i=0; i<10; i++){
		q->push(q, (void *)i);
	}
	printf("count: %d\n", q->count);
	while(q->size(q)) {
		printf("count: %d", q->size(q));
		e = (QElem *)q->pop(q);
		printf(" %d\n", (int)e->elem);
	}
}
