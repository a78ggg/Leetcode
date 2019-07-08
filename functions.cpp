#include "functions.h"

LeetFunc::LeetFunc()
{
}

LeetFunc::~LeetFunc()
{
}


std::vector<int> LeetFunc::twoSum(std::vector<int>& nums, int target)
{

#pragma region 直覺
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
#pragma endregion

#pragma region unordered_map
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
#pragma endregion

}

ListNode* LeetFunc::addTwoNumbers(ListNode* l1, ListNode* l2)
{
#pragma region RunTime error
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
#pragma endregion

#pragma region Good Answer
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
#pragma endregion

}