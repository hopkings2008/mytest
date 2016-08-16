#ifndef TEST_LCS_H
#define TEST_LCS_H

#include "lcs.h"
#include <gtest/gtest.h>

class LcsTest: public ::testing::Test {
	public:
		LcsTest();
		virtual ~LcsTest();
		virtual void SetUp();
		virtual void TearDown();
	protected:
		Lcs m_lcs;
};

#endif
