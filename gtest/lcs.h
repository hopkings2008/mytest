#ifndef LCS_H
#define LCS_H
#include <string>
#include <vector>
#include <iostream>

class Lcs {
	public:
		Lcs();
		virtual ~Lcs();
		int findLcs(const std::vector<int> &v1, const std::vector<int> &v2);
};

#endif
