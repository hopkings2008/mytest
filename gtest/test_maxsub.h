#pragma once

#include "maxsub.h"
#include <gtest/gtest.h>

class MaxSubTest: public ::testing::Test {
	public:
		MaxSubTest();
		virtual ~MaxSubTest();
		virtual void SetUp();
		virtual void TearDown();
	protected:
		MaxSub m_maxSub;
};

