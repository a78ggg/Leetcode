#include "functions.h"
#include <sstream>
#include <math.h>

LeetFunc::LeetFunc()
{
}
LeetFunc::~LeetFunc()
{
}
std::vector<int> LeetFunc::twoSum(std::vector<int>& nums, int target)
{
    //unordered_map
    std::unordered_map<int, int> item;//<nums:value,nums:index>
    std::vector<int> ans;
    for (int i = 0; i < nums.size(); i++)
    {
        int curValue = nums.at(i);
        int addValue = target - curValue;
        std::unordered_map<int, int>::iterator iter = item.find(addValue);
        if (iter != item.end())
        {
            ans.push_back(iter->second);
            ans.push_back(i);
            return ans;
        }
        else
        {
            item[nums[i]] = i;
        }
    }
    return ans;
}
ListNode* LeetFunc::addTwoNumbers(ListNode* l1, ListNode* l2)
{
    ListNode Ans(0);
    ListNode *p = &Ans;

    int extra = 0;
    while (l1 || l2 || extra)
    {
        int sum = (l1 == NULL ? 0 : l1->val) + (l2 == NULL ? 0 : l2->val) + extra;
        extra = sum / 10;
        p->next = new ListNode(sum % 10);
        p = p->next;
        l1 = l1 == NULL ? l1 : l1->next;
        l2 = l2 == NULL ? l2 : l2->next;
    }
    return Ans.next;
}
int LeetFunc::lengthOfLongestSubstring(std::string s)
{
    //直覺unordered_map
    int maxSize = 0;
    int curIndex = -1;
    std::unordered_map<char, int> map;
    for (int i = 0; i < s.size(); i++)
    {
        char word = s[i];
        std::unordered_map<char, int>::iterator iter = map.find(word);
        if (iter != map.end())
        {
            curIndex = curIndex > iter->second ? curIndex : iter->second;
        }
        map[word] = i;
        maxSize = maxSize > i - curIndex ? maxSize : i - curIndex;
    }
    return maxSize;
}
double LeetFunc::findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
{
    int size1 = nums1.size();
    int size2 = nums2.size();
    int sum = size1 + size2;
    int times = (int)sum / 2 + 1;
    int last = 0;
    int cur = 0;
    int v1Index = -1;
    int v2Index = -1;
    for (int i = 0; i < times; i++)
    {
        last = cur;
        if (v1Index == size1 - 1)
        {
            cur = nums2[++v2Index];
        }
        else if (v2Index == size2 - 1)
        {
            cur = nums1[++v1Index];
        }
        else if (nums1[v1Index + 1] < nums2[v2Index + 1])
        {
            cur = nums1[++v1Index];
        }
        else
        {
            cur = nums2[++v2Index];
        }
    }
    if (sum % 2 == 0)return (double)(last + cur) / 2.0;
    else return cur;
}
std::string LeetFunc::longestPalindrome(std::string s)
{
    if (s.size() <= 1)return s;

    int maxLength = 0;
    int maxLeft = 0;
    //find mid and explore left and right side
    for (int mid = 0; mid < s.size();)
    {
        int left = mid;
        int right = mid;
        while (right < s.size() && s[right] == s[right + 1])
        {
            right++;
        }
        mid = right + 1;

        //expand from mid point
        while (left > 0 && right < s.size() - 1 && s[left - 1] == s[right + 1])
        {
            left--;
            right++;
        }
        int curLength = right - left + 1;
        if (curLength > maxLength)
        {
            maxLength = curLength;
            maxLeft = left;
        }
    }
    return s.substr(maxLeft, maxLength);
}
int LeetFunc::reverse(int x)
{
    long long ans = 0;
    while (x)
    {
        ans = ans * 10 + x % 10;
        x /= 10;
    }
    return (ans > INT_MAX || ans < INT_MIN) ? 0 : (int)ans;
}
bool LeetFunc::isPalindrome(int x)
{
    std::stringstream ss;
    ss << x;
    std::string str = ss.str();
    ss.str("");
    ss.clear();

    int left = 0;
    int right = str.size() - 1;
    int mid = (ceil)((double)(str.size() / 2.0));
    while (left < mid)
    {
        if (str[left] != str[right])return false;
        left++;
        right--;
    }
    return true;
}
int LeetFunc::maxArea(std::vector<int>& height)
{
//Ver.1 good algo.
#if 1
    int maxA = 0;
    int l = 0, r = height.size() - 1;
    while (l < r)
    {
        int h = height[l] < height[r] ? height[l] : height[r];
        maxA = maxA > h*(r - l) ? maxA : h * (r - l);
        while (height[l] <= h && l < r)l++;
        while (height[r] <= h && l < r)r--;
    }
    return maxA;
#endif

//Ver. 0 速度慢
#if 0
    int maxA = 0;
    for (int i = 0; i < height.size(); i++)
    {
        int curHeight = height.at(i);
        for (int j = 0; j < height.size(); j++)
        {
            int findHeight = height.at(j);
            if (curHeight <= findHeight)
            {
                int curA = curHeight * abs(i - j);
                if (maxA < curA)maxA = curA;
            }
        }
    }
    return maxA;
#endif
}
std::string LeetFunc::longestCommonPrefix(std::vector<std::string>& strs)
{
    if (strs.size() <= 0)return "";

    std::string base = strs.at(0);
    int r = base.size();
    for (int i = 1; i < strs.size(); i++)
    {
        std::string cur = strs.at(i);
        int l = 0;
        r = r < cur.size() ? r : cur.size();
        while (base[l] == cur[l] && l < r)l++;
        r = l;
    }
    return base.substr(0, r);
}