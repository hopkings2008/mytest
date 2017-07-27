#pragma once


#include <aver.h>
#include <gtest/gtest.h>

class AverTest: public ::testing::Test {
	public:
		AverTest();
		virtual ~AverTest();
		virtual void SetUp();
		virtual void TearDown();
	protected:
		ImageAverage m_aver;
};

