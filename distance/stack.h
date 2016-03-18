#include <stdlib.h>
#include <stdio.h>

#define STACK_MAX 100


typedef struct Elem {
	struct Elem *next;
	void *val;
} Elem;

typedef struct Stack {
	Elem * head;
	int     size;
	void* (*pop)(struct Stack *);
	void (*push)(struct Stack *, void *);
}Stack;

Stack *CreateStack();

void FreeStack(Stack *s);
