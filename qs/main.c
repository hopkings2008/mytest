#include <stdio.h>

void qsort(int a[], int len);

int main(int argc, char *argv[]) {
	int a[5] = {3, 1, 2, 5, 4};
	qsort(a, 5);
	for(int i=0; i < 5; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}

void qsort(int a[], int len) {
	int pos = -1;
	if (len <= 1)
		return;

	int star = a[len-1];

	for ( int i = 0; i < len -1; i++ ) {
		if ( a[i] < star ) {
			int temp = a[++pos];
			a[pos] = a[i];
			a[i] = temp;
		}
	}

	a[len-1] = a[++pos];
	a[pos] = star;
	qsort(a, pos);
	qsort(a+pos+1, len-pos);
}
