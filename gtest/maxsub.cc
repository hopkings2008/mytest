#include "maxsub.h"

Record::Record():start(0), end(0), max(0){
}

Record::Record(const Record &other):start(other.start), end(other.end), max(other.max){
}

Record & Record::operator=(const Record &other){
    if (this == &other){
        return *this;
    }
    start = other.start;
    end = other.end;
    max = other.max;
    return *this;
}

MaxSub::MaxSub(){
}

MaxSub::~MaxSub(){
}

int MaxSub::find(const std::vector<int> &array, std::vector<Record> &result){
    if (array.empty()){
        return 0;
    }
    size_t num = array.size();
    Record ir;
    ir.start = 0;
    ir.end = 0;
    ir.max = array[0];
    // array[0] max subarray is itself.
    result.push_back(ir);
    for (size_t j=1; j<num; j++){
        const Record &former = result[j-1];
        Record rc;
        rc.max = former.max-1;
        rc.end = j;
        int sum = 0;
        // compare sum & former.max. rc.max is the sum if sum >= former.max.
        for (int k = j; k > former.end; k--){
            sum += array[k];
            if (sum >= former.max && sum > rc.max){
                rc.start = k;
                rc.max = sum;
            }
        }
        // compare sum + former.max and former.max
        if (sum + former.max > former.max && sum + former.max > rc.max){
            rc.start = former.start;
            rc.max = sum + former.max;
        }
        // check rc.max and former.max
        if (rc.max < former.max){
            rc.max = former.max;
            rc.start = former.start;
            rc.end = former.end;
        }
        result.push_back(rc);
    }
    return result.back().max;
}

int MaxSub::maxSubArray(std::vector<int>& nums) {
    std::vector<int> sums;
    int end = 0;
    size_t num = nums.size();
    for (size_t i=0; i<num; i++){
        if (0 == i){
            sums.push_back(nums[i]);
            continue;
        }
        int tempEnd = i;
        int former = sums[i-1];
        int max = former-1;
        int sum = 0;
        for (int j=i; j>end; j--){
            sum += nums[j];
            if (sum >= former && sum > max){
                max = sum;
                continue;
            }
        }
        if (sum + former >= former && sum + former > max){
            max = sum+former;
        }
        if (max < former){
            max = former;
            tempEnd = end;
        }
        end = tempEnd;
        sums.push_back(max);
    }
    return sums.back();        
}
