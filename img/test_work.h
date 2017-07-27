#pragma once


#include "work.h"
#include <gtest/gtest.h>

class WorkTest: public ::testing::Test {
	public:
		WorkTest();
		virtual ~WorkTest();
		virtual void SetUp();
		virtual void TearDown();
	protected:
		Work m_work;
};

