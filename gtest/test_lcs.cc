#include "test_lcs.h"
#include <iostream>


LcsTest::LcsTest():m_lcs() {
}

LcsTest::~LcsTest(){
}

void LcsTest::SetUp() {
}

void LcsTest::TearDown() {
}

TEST_F(LcsTest, TestBasic) {
	int a[] = {1,4,2,3,3,4,1};
	int b[] = {4,1,1,2,3,3};
	std::vector<int> v1(a, a+sizeof(a)/sizeof(int));
	std::vector<int> v2(b, b+sizeof(b)/sizeof(int));

	int max = m_lcs.findLcs(v1, v2);
	std::cout<<"got lcs number: "<<max<<std::endl;
	//ASSERT_EQ(4, max);
}
