#include <palindromic.h>
#include <vector>
#include <set>

Palindromic::Palindromic(){
}

Palindromic::~Palindromic(){}

std::string Palindromic::longestPalindrome(std::string s){
    //first array: each character postion.
    //second set: palindrome length.
    //by default, all the characters contains the palindrome itself.
    std::vector<std::set<int>> poss;
    int max = 0;
    int start = 0;
    int total = s.length();
    if(total == 0 || total == 1){
        return s;
    }

    poss.resize(total);
    // first check the longest case.
    int allMatch = 1;
    for(int a=0,b=total-1; a<=b; a++, b--){
        if(s[a] == s[b]){
            continue;
        }
        allMatch = 0;
        break;
    }

    if(1 == allMatch){
        return s;
    }

    for (int j=0; j<total;j++){
        for(int i=0; i<total; i++){
            if (j>=total-i){
                break;
            }
            int a = i;
            int b = i+j;
            int match = 1;
            //precheck
            if(a+1<b && j-2>0){
                if(poss[a+1].find(j-2) != poss[a+1].end()){
                    if(s[a] == s[b]){
                        if(max < j){
                            max = j;
                            start = i;
                        }
                        poss[a].insert(j);
                    }
                }
                continue;
            }

            while(a<=b){
                if(s[a++] == s[b--]){
                    continue;
                }
                match = 0;
                break;
            }
            if (1 == match){
                if(max < j){
                    max = j;
                    start = i;
                }
                poss[i].insert(j);
            }
        }
    }

    return s.substr(start, max+1);
}

std::string Palindromic::longestPalindrome2(std::string s){
    int total = s.length();
    if(total ==0 || total==1){
        return s;
    }
    Pos max = findPalind(s, 0, total-1);
    return s.substr(max.start, max.len+1);
}

Pos Palindromic::findPalind(std::string s, int start, int end){
    int total = s.length();
    Pos max(-1, 0);
    if(start > end){
        // return "";
        return max;
    }
    if(start == end){
        int a = start -1;
        int b = start +1;
        while(a>=0 && b<=total-1){
            if(s[a] == s[b]){
                a--;
                b++;
                continue;
            }
            break;
        }
        if(a+1 > b-1){
            max.start = start;
            max.len = 0;
        } else {
            max.start = a+1;
            max.len = b-a-2;
        }
        return max;
    }
    int mid = (end+start)/2;
    // even
    if((end-start+1)%2==0){
        int mid2 = mid+1;
        int a = mid;
        int b = mid2;
        // center a,b
        while(a>=0 && b<=total-1){
            if(s[a] == s[b]){
                a--;
                b++;
                continue;
            }
            break;
        }
        if(a+1 > b-1){
            max.start=a;
            max.len = 0;
        } else {
            max.start = a+1;
            max.len = b-1-(a+1);
        }
        if(max.len == total-1){
            return max;
        }
        // center mid
        // center mid2
        //get left maximum
        if(start <= mid){
            Pos left = findPalind(s, start, mid);
            // get the maximum
            if (max.len < left.len){
                max.len = left.len;
                max.start = left.start;
            }
        }
        //get right maximum
        if(mid2 <= end){
            Pos right = findPalind(s, mid2, end);
            //get the maximum
            if (max.len < right.len){
                max.len = right.len;
                max.start = right.start;
            }
        }
        return max;
    }
    //odd
    int a = mid;
    int b = mid;
    while(a>=0 && b <= total-1){
        if(s[a] == s[b]){
            a--;
            b++;
            continue;
        }
        break;
    }
    if(a+1 > b-1){
        max.start = mid;
        max.len = 0;
    } else {
        max.start = a+1;
        max.len = b-a-2;
    }
    if(max.len == total-1){
        return max;
    }
    if (start <= mid){
        Pos left = findPalind(s, start, mid);
        if(max.len < left.len){
            max.start = left.start;
            max.len = left.len;
        }
    }
    if(mid <= end) {
        Pos right = findPalind(s, mid, end);
        if(max.len < right.len){
            max.start = right.start;
            max.len = right.len;
        }
    }
    
    return max;
}
