#pragma once


#include "num_tree.h"
#include <gtest/gtest.h>

class NumTreeTest: public ::testing::Test {
	public:
		NumTreeTest();
		virtual ~NumTreeTest();
		virtual void SetUp();
		virtual void TearDown();
	protected:
		NumTree m_tree;
};

