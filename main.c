#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int minDistance(const char *s, char src, char dest);

int main(int argc, char *argv[]) {
	const char *s="a1b2c3d4e3f4g2h3";
	int dis = minDistance(s, 'd', 'g');
}

int minDistance(const char *s, char src, char dest) {
	int dis = -1;;
	Node *tree = treeInit(s);
	if(!tree){
		printf("failed to create tree\n");
		return 0;
	}

	treePrint(tree);

	dis = getDistance(tree, src, dest);
	printf("%c-->%c: %d\n", src, dest, dis);
	return dis;
}
