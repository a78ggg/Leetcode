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