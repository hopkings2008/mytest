#include "lcs.h"

Lcs::Lcs() {
}

Lcs::~Lcs() {
}

int Lcs::findLcs(const std::vector<int> &v1, const std::vector<int> &v2) {
	int m = v1.size();
	int n = v2.size();
	int **a = (int **)new int[m+1]();
	int max = 0;
	int *temp = new int[(m+1)*(n+1)]();
	for (int i=0; i<=m; i++){
		a[i] = temp + i*(n+1);
	}

	/*for ( int i=0; i<=m; i++ ){
		a[i][0] = 0;
	}

	for (int i=1; i<=n; i++) {
		a[0][i] = 0;
	}

	for (int i=1; i<=m; i++) {
		for (int j=1; j<=n; j++) {
			if (v1[i-1] == v2[j-1]) {
				a[i][j] = a[i-1][j-1] + 1;
				continue;
			}
			if(a[i-1][j] >= a[i][j-1]){
				a[i][j] = a[i-1][j];
			} else {
				a[i][j] = a[i][j-1];
			}
		}
	}

	max = a[m][n];*/

	delete[] temp;
	delete[] a;

	return max;
}
