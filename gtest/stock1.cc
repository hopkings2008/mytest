#include <stock1.h>

Stock1::Stock1(){
}

Stock1::~Stock1(){
}

int Stock1::maxProfit(const std::vector<int> &prices){
    // max & min are indexes of values in the array.
    int start = 0;
    int end = 0;
    int min = 0;
    int num = (int)prices.size();

    for (int i=0; i<num; i++){
        if (prices[i] - prices[min] > prices[end] - prices[start]){
            end = i;
            start = min;
        }
        if (prices[i] < prices[min]){
            min = i;
        }
    }

    return prices[end] - prices[start];
}
