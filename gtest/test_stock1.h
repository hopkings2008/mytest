#pragma once


#include "stock1.h"
#include <gtest/gtest.h>

class Stock1Test: public ::testing::Test {
	public:
		Stock1Test();
		virtual ~Stock1Test();
		virtual void SetUp();
		virtual void TearDown();
	protected:
		Stock1 m_stock;
};

