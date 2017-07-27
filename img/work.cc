#include "work.h"
#include <string>
#include <iostream>

Work::Work() {
	m_val = L"this is worker.";
}

Work::~Work() {
	m_val = L"";
}

void Work::show() {
	std::wcout<<m_val<<std::endl;
}
