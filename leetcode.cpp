#include "functions.h"
#include <iostream>

int main()
{
    LeetFunc test;
    std::vector<int> a{ 1,2,3 };

    std::vector<std::vector<char>> board{
    {'a','b','c','e' },
    {'s','f','c','s'},
    {'a','d','e','e'} };
    test.exist(board, "abcced");
}