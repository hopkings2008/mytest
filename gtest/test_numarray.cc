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
    //int ns[] = {-2,0,3,-5,2,-1};
    int ns[] = {-8261,2300,-1429,6274,9650,-3267,1414,-8102,6251,-5979,-5291,-4616,-4703};
    std::vector<int> nums;
    nums.assign(ns, ns + sizeof(ns)/sizeof(int));
    m_numArray = new NumArray(nums);
    int sum = m_numArray->sumRange(0, 8);
    ASSERT_EQ(sum, 4830);
    /*sum = m_numArray->sumRange(2,5);
    ASSERT_EQ(sum, -1);
    sum = m_numArray->sumRange(0,5);
    ASSERT_EQ(sum, -3);*/
}
