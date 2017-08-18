#include "test_numtree.h"
#include <iostream>

NumTreeTest::NumTreeTest() {
	std::wcout<<L"num_treetest begin"<<std::endl;
}

NumTreeTest::~NumTreeTest() {
	std::wcout<<L"num_treetest end"<<std::endl;
}

void NumTreeTest::SetUp() {
}

void NumTreeTest::TearDown() {
}

TEST_F(NumTreeTest, TestShow) {
	int n = m_tree.numTrees(3);
    ASSERT_EQ(n, 5);
    n = m_tree.numTrees(4);
    ASSERT_EQ(n, 14);
    for (int i=5; i<=20; i++){
        n = m_tree.numTrees(i);
        printf("num: %d, %d\n", i, n);
    }
}
