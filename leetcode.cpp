#include "functions.h"
#include <iostream>

int main()
{
    LeetFunc test;
    std::vector<int> v_int{ 2,2,1,1 };
    std::string str = "bbabbb";

    test.longestPalindrome(str);
    test.uniquePaths(19, 13);
}