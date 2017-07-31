#pragma once


#include <rob.h>
#include <gtest/gtest.h>

class RobTest: public ::testing::Test {
	public:
		RobTest();
		virtual ~RobTest();
		virtual void SetUp();
		virtual void TearDown();
	protected:
		Rob m_rob;
};

