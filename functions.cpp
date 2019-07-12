#include "functions.h"
#define USED 0
#define Good 1
LeetFunc::LeetFunc()
{
}
LeetFunc::~LeetFunc()
{
}
std::vector<int> LeetFunc::twoSum(std::vector<int>& nums, int target)
{
    //unordered_map
    if (Good)
    {
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
    //直覺
    else if (USED)
    {
    int first = -1;
    int second = -1;
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = i + 1; j < nums.size(); j++)
        {
            int a = nums[i];
            int b = nums[j];
            if (a + b == target)
            {
                first = i;
                second = j;
                break;
            }
        }
    }
    std::vector<int> ans{ first,second };
    return ans;
    }
}
ListNode* LeetFunc::addTwoNumbers(ListNode* l1, ListNode* l2)
{
    if (Good)
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

    //RunTime error
    else if (USED == 0)
    {
    int value = 0;
    int digital = 0;
    while (l1 != NULL)
    {
        value += l1->val*pow(10, digital);
        l1 = l1->next;
        digital++;
    }

    int value2 = 0;
    int digital2 = 0;
    while (l2 != NULL)
    {
        value2 += l2->val*pow(10, digital2);
        l2 = l2->next;
        digital2++;
    }

    int add = value + value2;
    ListNode preHead(0);
    ListNode *ans = &preHead;
    while (add)
    {
        ans->next = new ListNode(add % 10);
        add /= 10;
        ans = ans->next;
    }
    return preHead.next;
    }
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
        while (left>0 && right<s.size()-1&&s[left-1] ==s[right+1])
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
    if (Good)
    {
        long long ans = 0;
        while (x)
        {
            ans = ans * 10 + x % 10;
            x /= 10;
        }
        return (ans > INT_MAX || ans < INT_MIN) ? 0 : (int)ans;
    }
    // overflow
    else if (USED)
    {
    bool isPositive = x > 0 ? true : false;
    long long pos_x = abs(x);
    std::vector<int> reverse_Link;
    while (pos_x > 0)
    {
        reverse_Link.push_back(pos_x % 10);
        pos_x = pos_x / 10;
    }
    int ans = 0;
    int power = reverse_Link.size() - 1;
    for (int i = 0; i < reverse_Link.size(); i++)
    {
        ans += reverse_Link[i] * pow(10, power--);
    }
    return isPositive ? ans : ans * (-1);
    }

}