#include <stdlib.h>

typedef struct Node{
	struct Node *parent;
	struct Node *left;
	struct Node *right;
	char c;
}Node;

Node *treeInit(const char *s);
void treePrint(const Node *root);
