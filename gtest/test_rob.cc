#include <test_rob.h>
#include <iostream>

RobTest::RobTest() {
	std::wcout<<L"robtest begin"<<std::endl;
}

RobTest::~RobTest() {
	std::wcout<<L"robtest end"<<std::endl;
}

void RobTest::SetUp() {
}

void RobTest::TearDown() {
}

TEST_F(RobTest, TestShow) {
    int a[4] = {1, 1, 1, 2};
    std::vector<int> nums;
    nums.assign(a, a+4);
    int max = m_rob.rob(nums);
    ASSERT_EQ(max, 3);
    int b[4] = {2, 1, 1, 1};
    nums.clear();
    nums.assign(b, b+4);
    max = m_rob.rob(nums);
    ASSERT_EQ(max, 3);
    int c[5] = {1, 3, 5, 4, 6};
    nums.clear();
    nums.assign(c, c+5);
    max = m_rob.rob(nums);
    ASSERT_EQ(max, 12);
    int d[4] = {2, 1, 1, 2};
    nums.clear();
    nums.assign(d, d+4);
    ASSERT_EQ(max, 3);
}
