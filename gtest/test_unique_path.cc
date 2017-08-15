#include "test_unique_path.h"
#include <iostream>

UniquePathTest::UniquePathTest() {
	std::wcout<<L"unique_path_test begin"<<std::endl;
}

UniquePathTest::~UniquePathTest() {
	std::wcout<<L"unique_path_test end"<<std::endl;
}

void UniquePathTest::SetUp() {
}

void UniquePathTest::TearDown() {
}

TEST_F(UniquePathTest, TestShow) {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(0);
    std::vector<std::vector<int>> array;
    array.push_back(v);
    int num = m_path.pathNums(array);
    ASSERT_EQ(num, 0);
}
