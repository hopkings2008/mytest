#include "test_work.h"
#include <iostream>

WorkTest::WorkTest():m_work() {
	std::wcout<<L"worktest begin"<<std::endl;
}

WorkTest::~WorkTest() {
	std::wcout<<L"worktest end"<<std::endl;
}

void WorkTest::SetUp() {
}

void WorkTest::TearDown() {
}

TEST_F(WorkTest, TestShow) {
	m_work.show();
}
