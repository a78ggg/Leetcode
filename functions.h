﻿#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class LeetFunc
{
public:
    LeetFunc();
    ~LeetFunc();

    //No.1
    std::vector<int> twoSum(std::vector<int>& nums, int target);
    //No.2
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
    //No.3
    int lengthOfLongestSubstring(std::string s);
    //No.4
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2);
    //No.5
    std::string longestPalindrome(std::string s);
    //No.7
    int reverse(int x);
    //No.9
    bool isPalindrome(int x);
    //No.11
    int maxArea(std::vector<int>& height);
    //No.14
    std::string longestCommonPrefix(std::vector<std::string>& strs);
    //No.15
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums);
    //No.16
    int threeSumClosest(std::vector<int>& nums, int target);
    //No.17
    std::vector<std::string> letterCombinations(std::string digits);
    //No.18
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target);
    //No.19
    ListNode* removeNthFromEnd(ListNode* head, int n);
    //No.20
    bool isValid(std::string s);
    //No.21
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);
    //No.22
    void helper(std::string s, int left, int right);
    std::vector<std::string> generateParenthesis(int n);
    //No.23
    ListNode* MergeTwoList(ListNode* L1, ListNode* L2);
    ListNode* mergeKLists(std::vector<ListNode*>& lists);
    //No.24
    ListNode* swapPairs(ListNode* head);
    //No.25
    ListNode* reverseKGroup(ListNode* head, int k);
    //No.32
    int longestValidParentheses(std::string s);
    //No.33
    int search(std::vector<int>& nums, int target);
    //No.34
    std::vector<int> searchRange(std::vector<int>& nums, int target);
    //No.35
    int searchInsert(std::vector<int>& nums, int target);
    //No.36
    bool isValidSudoku(std::vector<std::vector<char>>& board);
    //No.37
    bool isValid(std::vector<std::vector<char>>& board, int row, int col, char value);
    bool solveSudoku(std::vector<std::vector<char>>& board, int row, int col);
    void solveSudoku(std::vector<std::vector<char>>& board);
    //No.39
    void combinationSum(std::vector<int>& candidates, int target, std::vector<std::vector<int>> &ans, std::vector<int> &sum, int left);
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target);
    //No.40
    void combinationSum2(std::vector<int>& candidates, int target, std::vector<std::vector<int>> &vvans, std::vector<int> &vsum, int left);
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target);
    //No.41
    int firstMissingPositive(std::vector<int>& nums);
    //No.42
    int trap(std::vector<int>& height);
    //No.44
    bool isMatch(std::string s, std::string p);
    //No.45
    int jump(std::vector<int>& nums);
    //No.46
    void permute(std::vector<int>& nums, int begin, std::vector<std::vector<int>> &vvans);
    std::vector<std::vector<int>> permute(std::vector<int>& nums);
    //No.47
    void permuteUnique(std::vector<int> nums, int pos, std::vector<std::vector<int>> &vvans);
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums);
    //No.48
    void rotate(std::vector<std::vector<int>>& matrix);
    //No.49
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs);
    //No.53
    int maxSubArray(std::vector<int>& nums);
    //No.55
    bool canJump(std::vector<int>& nums);
    //No.56
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals);
    //No.57
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval);
    //No.60
    int m_count;
    void getPermutation(std::string &s_input, std::string &s_ans, int index, int target);
    std::string getPermutation(int n, int k);
    //No.62
    int uniquePaths(int m, int n);
private:
    std::vector<std::string> result;
};

#endif

