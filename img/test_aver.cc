#include <test_aver.h>
#include <iostream>

AverTest::AverTest() {
	std::wcout<<L"avertest begin"<<std::endl;
}

AverTest::~AverTest() {
	std::wcout<<L"avertest end"<<std::endl;
}

void AverTest::SetUp() {
}

void AverTest::TearDown() {
}

TEST_F(AverTest, TestBasicFunc) {
    std::string file = "./imgs/1.jpg";
    util::Error err = m_aver.init(file);
    ASSERT_EQ(err.code(), 0);
    cv::Mat out(m_aver.rowNum(), m_aver.colNum(), CV_8UC3);
    err = m_aver.average(out);
    ASSERT_EQ(err.code(), 0);
    err = m_aver.save("./imgs", "out");
    ASSERT_EQ(err.code(), 0);
}
