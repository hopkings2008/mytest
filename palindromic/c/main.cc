#include <stdlib.h>
#include <palindromic.h>

int main(int argc, char *argv[]){
    Palindromic palind;
    std::string p = palind.longestPalindrome2(argv[1]);
    printf("p: %s, length: %lu\n", p.c_str(), p.length());
    return 0;
}