#include "test_maxsub.h"
#include <iostream>


MaxSubTest::MaxSubTest():m_maxSub() {
}

MaxSubTest::~MaxSubTest(){
}

void MaxSubTest::SetUp() {
}

void MaxSubTest::TearDown() {
}

TEST_F(MaxSubTest, TestBasic) {
	int a[] = {1,4,2,3,3,4,1};
	//int b[] = {4,1,1,2,3,3};

    std::vector<int> array;
    std::vector<Record> result;
    array.assign(a, a+sizeof(a)/sizeof(int));
	int max = m_maxSub.find(array, result);
    const Record & rc = result.back();
	printf("start: %d, end: %d, max: %d\n", rc.start, rc.end, rc.max);
	ASSERT_EQ(18, max);
}

TEST_F(MaxSubTest, TestSmall1) {
	//int a[] = {1,2, -5, -6, 3, 4};
    int a[] = {-2,1,-3,4,-1,2,1,-5,4};
	//int b[] = {4,1,1,2,3,3};

    std::vector<int> array;
    std::vector<Record> result;
    array.assign(a, a+sizeof(a)/sizeof(int));
	int max = m_maxSub.find(array, result);
    const Record & rc = result.back();
	printf("start: %d, end: %d, max: %d\n", rc.start, rc.end, rc.max);
    size_t num = result.size();
    for (size_t i=0; i<num; i++){
        printf("idx: %d, start: %d, end: %d, max: %d\n", (int)i, result[i].start, result[i].end, result[i].max);
    }
    ASSERT_EQ(6, max);
}
