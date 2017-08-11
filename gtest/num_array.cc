#include <num_array.h>
#include <stdio.h>

NumArray::NumArray(const std::vector<int> &nums){
    m_size = (int)nums.size();
    for (int i=0; i<m_size; i++){
        if (0 == i){
            m_nums.push_back(nums[i]);
            continue;
        }
        m_nums.push_back(nums[i] + m_nums[i-1]);
    }
}

int NumArray::sumRange(int i, int j){
    if (i > j){
        return 0;
    }
    if (i >= m_size){
        return 0;
    }
    if (i > 0){
        return m_nums[j] - m_nums[i-1];
    }
    return m_nums[j];
}

