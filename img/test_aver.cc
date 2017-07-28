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

TEST_F(AverTest, TestBasicAverageFunc) {
    std::string file = "./imgs/1.jpg";
    m_aver.setRange(3);
    util::Error err = m_aver.init(file);
    ASSERT_EQ(err.code(), 0);
    printf("depth: %d\n", m_aver.depth());
    cv::Mat out(m_aver.rowNum(), m_aver.colNum(), CV_8UC3);
    err = m_aver.average(out);
    ASSERT_EQ(err.code(), 0);
    err = m_aver.save(out, "./imgs", "out");
    ASSERT_EQ(err.code(), 0);
    cv::Mat inv(m_aver.rowNum(), m_aver.colNum(), CV_8UC3);
    err = m_aver.inverse(inv);
    ASSERT_EQ(err.code(), 0);
    err = m_aver.save(inv, "./imgs", "inv");
}
