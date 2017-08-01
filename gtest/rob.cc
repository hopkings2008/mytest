#include <rob.h>
#include <stdio.h>

Rob::Rob(){
}

Rob::~Rob(){
}

int Rob::rob(std::vector<int> &nums){
    int max = 0;
    int secondmax = 0;
    int lastidx = -1;

    int num = (int)nums.size();
    for (int i = 0; i<num; i++){
        if (-1 == lastidx){
            lastidx = i;
            max = nums[i];
            printf("accept %d, max: %d, idx: %d, second: %d\n", i, max, lastidx, secondmax);
            continue;
        }
        if (lastidx + 1 < i){
            max += nums[i];
            lastidx = i;
            printf("accept %d, max: %d, idx: %d, second: %d\n", i, max, lastidx, secondmax);
            continue;
        }
        // lastidx + 1 == i.
        if (nums[i] > nums[lastidx]){
            if (max - nums[lastidx] + nums[i] > nums[i] + secondmax){
               secondmax = max;
               max = max - nums[lastidx] + nums[i];
               lastidx = i;
               continue;
            }
            int temp = max;
            max = nums[i]+secondmax;
            lastidx = i;
            secondmax = temp;
            continue;
        }
        if (nums[i] + secondmax > max){
            int temp = max;
            max = nums[i] + secondmax;
            printf("remove %d and accept %d, max: %d, second: %d\n", lastidx, i, max, secondmax);
            lastidx = i;
            secondmax = temp;
            continue;
        }
        secondmax += nums[i];
    }
    return max;
}
