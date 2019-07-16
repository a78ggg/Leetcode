#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>

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
    //No.6
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
private:

};

#endif

