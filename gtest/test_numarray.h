#pragma once


#include <num_array.h>
#include <gtest/gtest.h>

class NumArrayTest: public ::testing::Test {
	public:
		NumArrayTest();
		virtual ~NumArrayTest();
		virtual void SetUp();
		virtual void TearDown();
	protected:
		NumArray *m_numArray;
};

