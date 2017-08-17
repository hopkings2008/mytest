#include <num_tree.h>
#include <string.h>

NumTree::NumTree(){
}

NumTree::~NumTree(){
}

int NumTree::numTrees(int n){
    int sum[n+1][n+1];
    memset(sum, 0, sizeof(sum)/sizeof(int));

    for (int i=1; i<=n; i++){
        sum[i][i] = 1;
    }

    for (int j=1; j<=n-1; j++){
        for (int i=1; i+j<=n; i++){
            sum[i][i+j] = sum[i+1][i+j] + sum[i][i+j-1];
            for (int k=i+1; k<=i+j-1; k++){
                sum[i][i+j] += sum[i][k-1]*sum[k+1][i+j];
            }
        }
    }

    return sum[1][n];
}
