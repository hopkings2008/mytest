#pragma once

#include <vector>

class UniquePath{
    public:
        UniquePath();
        ~UniquePath();

        int pathNums(std::vector<std::vector<int>>& obstacleGrid);
};
