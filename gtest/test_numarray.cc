#include <test_numarray.h>
#include <iostream>

NumArrayTest::NumArrayTest():m_numArray() {
	std::wcout<<L"numarray begin"<<std::endl;
}

NumArrayTest::~NumArrayTest() {
	std::wcout<<L"numarray end"<<std::endl;
}

void NumArrayTest::SetUp() {
}

void NumArrayTest::TearDown() {
}

TEST_F(NumArrayTest, TestShow) {
    int ns[] = {-2,0,3,-5,2,-1};
    std::vector<int> nums;
    nums.assign(ns, ns + sizeof(ns)/sizeof(int));
    m_numArray = new NumArray(nums);
    int sum = m_numArray->sumRange(0, 2);
    ASSERT_EQ(sum, 1);
}
