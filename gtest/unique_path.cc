#include <unique_path.h>

UniquePath::UniquePath(){
}

UniquePath::~UniquePath(){
}

int UniquePath::pathNums(std::vector<std::vector<int>> &obstacleGrid){
    int m = (int)obstacleGrid.size();
    if (0 == m){
        return 0;
    }
    int n = (int)obstacleGrid[0].size();
    if (0 == n){
        return 0;
    }
   
    std::vector<std::vector<int>> nums(m, std::vector<int>(n, 0));
    for (int i=0; i<m; i++){
        if (1 == obstacleGrid[i][0]){
            for (int k=i; k<m; k++){
                nums[i][0] = -1;
            }
            break;
        }
        nums[i][0] = 1;
    }

    for (int j=1; j<n; j++){
        if (1 == obstacleGrid[0][j]){
            for (int k = j; k<n; k++){
                nums[0][j] = -1;
            }
            break;
        }
        nums[0][j] = 1;
    }

    for (int i=1; i<m; i++){
        int n = (int)obstacleGrid[i].size();
        for (int j=1; j<n; j++){
            if (1 == obstacleGrid[i][j]){
                nums[i][j] = -1;
                continue;
            }
            if (-1 == nums[i-1][j] && -1 == nums[i][j-1]){
                nums[i][j] = -1;
            }
            if (-1 != nums[i-1][j]){
                nums[i][j] += nums[i-1][j];
            }
            if (-1 != nums[i][j-1]){
                nums[i][j] += nums[i][j-1];
            }
        }
    }

    return nums[m-1][n-1];
}
