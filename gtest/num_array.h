#pragma once

#include <vector>

class NumArray{
    public:
        NumArray(const std::vector<int> &nums);

        int sumRange(int i, int j);

    protected:
        std::vector<std::vector<int>> m_nums;
        int m_size;
};
