#include "stack.h"

void* pop(Stack *s) {
	Elem *elem = 0;
	void *val = 0;
	if(!s || !s->head) {
		return 0;
	}
	elem = s->head;
	s->head = elem->next;
	val = elem->val;
	free(elem);
	s->size--;
	return val;
}

void push(Stack *s, void *val) {
	Elem *elem = 0;
	if(!s) {
		return;
	}
	elem = malloc(sizeof(Elem));
	elem->val = val;
	elem->next = s->head;
	s->head = elem;
	s->size++;
}

Stack *CreateStack() {
	Stack *s = malloc(sizeof(Stack));
	s->pop = &pop;
	s->push = &push;
	s->head = 0;
	s->size = 0;
	return s;
}

void FreeStack(Stack *s) {
	Elem *elem = 0;
	if(!s)
		return;
	while(s->head){
		elem = s->head;
		s->head = elem->next;
		free(elem);
	}
	s->size = 0;
	s->head = 0;
	free(s);
}
