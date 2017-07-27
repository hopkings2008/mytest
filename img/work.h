#ifndef WORK_H
#define WORK_H
#include <string>

class Work {
	public:
		Work();
		virtual ~Work();
	public:
		void show();
	private:
		std::wstring  m_val;
};

#endif
