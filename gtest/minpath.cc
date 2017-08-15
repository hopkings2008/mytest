#include <minpath.h>

MinPath::MinPath(){
}

MinPath::~MinPath(){
}

int MinPath::minPathSum(std::vector<std::vector<int>> &grid){
    int m = (int)grid.size();
    if (0 == m){
        return 0;
    }

    int n = (int)grid[0].size();
    if (0 == n){
        return 0;
    }

    std::vector<std::vector<int>> sum(m, std::vector<int>(n, 0));
    sum[0][0] = grid[0][0];
    for (int i=1; i<m; i++){
        sum[i][0] += sum[i-1][0] + grid[i][0];
    }

    for (int j=1; j<n; j++){
        sum[0][j] += sum[0][j-1] + grid[0][j];
    }

    for (int i=1; i<m; i++){
        for (int j=1; j<n; j++){
            int min1 = sum[i][j-1] + grid[i][j];
            int min2 = sum[i-1][j] + grid[i][j];
            if (min1 < min2){
                sum[i][j] = min1;
                continue;
            }
            sum[i][j] = min2;
        }
    }


    return sum[m-1][n-1];
}
