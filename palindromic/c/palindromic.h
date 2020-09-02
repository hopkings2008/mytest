#include <string>

struct Pos{
    int start;
    int len;
    Pos():start(0),len(0){}
    Pos(int start, int len): start(start), len(len){}
};

class Palindromic {
    public:
    Palindromic();
    ~Palindromic();

    std::string longestPalindrome(std::string s);

    std::string longestPalindrome2(std::string s); 

    // start<=end
    Pos findPalind(std::string s, int start, int end);
};