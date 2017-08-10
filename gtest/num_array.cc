#include <num_array.h>

NumArray::NumArray(const std::vector<int> &nums): m_nums(nums.size(), std::vector<int>(nums.size(), 0)){
    m_size = (int)nums.size();
    for (int i=0; i<m_size; i++){
        for (int j=i; j<m_size; j++){
            m_nums[i][j] = m_nums[i][j-1] + nums[j];
        }
    }
}

int NumArray::sumRange(int i, int j){
    if (i > j){
        return 0;
    }
    if (i >= m_size){
        return 0;
    }

    return m_nums[i][j];
}
