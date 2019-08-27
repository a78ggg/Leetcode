#include "functions.h"
#include <iostream>

int main()
{
    LeetFunc test;
    //std::vector<int> v_int{ 2,2,1,1 };
    //std::string str = "bbabbb";

    //test.longestPalindrome(str);
    //test.uniquePaths(19, 13);

    std::vector<int> a{  };
    std::vector<int> b{  };
    std::vector<int> c{  };
    std::vector<std::vector<int>> vv;
    vv.push_back(a); vv.push_back(b); vv.push_back(c);
    test.searchMatrix(vv,1);
}