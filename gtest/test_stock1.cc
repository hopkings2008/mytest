#include "test_stock1.h"
#include <iostream>

Stock1Test::Stock1Test(){
	std::wcout<<L"Stock1Test begin"<<std::endl;
}

Stock1Test::~Stock1Test() {
	std::wcout<<L"Stock1Test end"<<std::endl;
}

void Stock1Test::SetUp() {
}

void Stock1Test::TearDown() {
}

TEST_F(Stock1Test, TestBasiczero) {
    std::vector<int> array = {7, 6, 5, 4, 3, 2, 1};
    int max = m_stock.maxProfit(array);
    printf("max: %d\n", max);
    ASSERT_EQ(max, 0);
}

TEST_F(Stock1Test, TestBasicVal) {
    std::vector<int> array = {7, 1, 5, 3, 6, 4};
    int max = m_stock.maxProfit(array);
    printf("max: %d\n", max);
    ASSERT_EQ(max, 5);
}
