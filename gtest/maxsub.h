#pragma once

#include <string>
#include <vector>

struct Record{
    int start;
    int end;
    int max;
    Record();
    Record(const Record &other);
    Record & operator=(const Record &other);
};

class MaxSub{
    public:
        MaxSub();
        ~MaxSub();

    public:
        int find(const std::vector<int> &array, std::vector<Record> &result);
};
