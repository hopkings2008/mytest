#include <stdio.h>
#include "tree.h"
#include "stack.h"

Node *nodeNew(){
	Node *p = (Node *)malloc(sizeof(Node));
	p->parent = 0;
	p->left = 0;
	p->right = 0;
	p->c = 0;
	return p;
}

Node *treeInit(const char *s) {
	Node *p = 0;
	Node *root = 0;
	int level = 0;

	for(; *s; s+=2) {
		if(s[1] - '0' > level) {
			if (0 == level) {
				root = nodeNew();
				root->c = s[0];
				level = s[1] - '0';
				p = root;
				if (*(s+1) == 0) {
					return root;
				}
				continue;
			}
			p->left = nodeNew();
			p->left->parent = p;
			p->left->c = s[0];
			level = s[1] - '0';
			p = p->left;
			if (*(s+1) == 0 ){
				return root;
			}
			continue;
		}

		while(s[1] - '0' < level) {
			p = p->parent;
			level--;
		}

		p = p->parent;
		p->right = nodeNew();
		p->right->c = s[0];
		p->right->parent = p;
		p = p->right;
		if(*(s+1) == 0){
			return root;
		}
	}

	return root;
}

void treePrint(const Node *root) {
	if(root){
		printf("%c\n", root->c);
	}
	if(root->left){
		printf("left:\n");
		treePrint(root->left);
	}
	if(root->right){
		printf("right:\n");
		treePrint(root->right);
	}
}

const Node *findNode(const Node *root, char c){
	const Node *p = 0;
	if(root && root->c == c){
		return root;
	}

	if(root->left) {
		p = findNode(root->left, c);
		if (p){
			return p;
		}
	}
	if(root->right){
		p = findNode(root->right, c);
		if(p){
			return p;
		}
	}

	return 0;
}

int getDistance(const Node * root, char c, char d){
	const Node *src = findNode(root, c);
	const Node *dest = findNode(root, d);
	Stack *srcStack = CreateStack();
	Stack *destStack = CreateStack();
	while(src){
		printf("src: %c\n", src->c);
		srcStack->push(srcStack, src);
 		src = src->parent;	
	}

	while(dest) {
		printf("dest: %c\n", dest->c);
		destStack->push(destStack, dest);
		dest = dest->parent;
	}

	while(srcStack->size != 0 && destStack->size != 0){
		src = (const Node *)srcStack->pop(srcStack);
		dest = (const Node *)destStack->pop(destStack);
		if(src != dest){
			srcStack->push(srcStack, src);
			destStack->push(destStack, dest);
			break;
		}
	}

	return srcStack->size + destStack->size;
}

