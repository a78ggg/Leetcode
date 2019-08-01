#include "functions.h"
#include <map>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <unordered_set>


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
std::vector<std::vector<int>> LeetFunc::threeSum(std::vector<int>& nums)
{
    std::vector<std::vector<int>> ans;

    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++)
    {
        int curValue = nums[i];
        int tarValue = -curValue;
        int s = i + 1, e = nums.size() - 1;

        if (tarValue < 0)break;

        while (s < e)
        {
            int sum = nums[s] + nums[e];
            if (sum < tarValue)s++;
            else if (sum > tarValue)e--;
            else
            {
                std::vector<int> curAns{ nums[i] ,nums[s] ,nums[e] };
                ans.push_back(curAns);

                while (s < e && nums[s] == curAns[1])s++;
                while (s < e && nums[e] == curAns[2])e--;
            }
        }
        while (i + 1 < nums.size() && nums[i] == nums[i + 1])i++;
    }
    return ans;
}
int LeetFunc::threeSumClosest(std::vector<int>& nums, int target)
{
    if (nums.size() < 3)return -1;

    int ans = nums[0] + nums[1] + nums[2];//初始值
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 2; i++)
    {
        int s = i + 1, e = nums.size() - 1;
        while (s < e)
        {
            int sum = nums[i] + nums[s] + nums[e];
            ans = fabs(sum - target) < fabs(ans - target) ? sum : ans;
            if (sum < target)s++;
            else if (sum > target)e--;
            else if (sum == target) return ans;
        }
    }
    return ans;
}
std::vector<std::string> LeetFunc::letterCombinations(std::string digits)
{
    if (digits.size() <= 0)return std::vector<std::string>();

    std::map<char, std::string> map{
        {'2',"abc"} ,{'3',"def"},{'4',"ghi"},
        {'5',"kjl"}, {'6',"mno"},{'7',"pqrs"},
        {'8',"tuv"},{'9',"wxyz"} };
    std::vector<std::string> letters;
    letters.push_back("");

    for (int i = 0; i < digits.size(); i++)
    {
        char cur = digits[i];
        if (cur<'2' || cur>'9')continue;
        std::string letter = map[cur];
        std::vector<std::string> tmp;
        for (int j = 0; j < letters.size(); j++)
        {
            for (int k = 0; k < letter.size(); k++)
            {
                tmp.push_back(letters[j] + letter[k]);
            }
        }
        letters = tmp;
        tmp.clear();
    }
    return letters;
}
std::vector<std::vector<int>> LeetFunc::fourSum(std::vector<int>& nums, int target)
{
    std::vector<std::vector<int>> ans
;
    if (nums.size() < 4)return ans;

    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 3; i++)
    {
        for (int j = i + 1; j < nums.size() - 2; j++)
        {
            int tarValue = target -(nums[i] + nums[j]);

            int s = j + 1, e = nums.size() - 1;
            while (s<e)
            {
                int sum = nums[s] + nums[e];
                if (sum < tarValue)s++;
                else if (sum > tarValue)e--;
                else
                {
                    std::vector<int> curAns{ nums[i],nums[j],nums[s],nums[e] };
                    ans.push_back(curAns);
                    while (s < e && nums[s] == curAns[2])s++;
                    while (s < e && nums[e] == curAns[3])e--;
                }
            }
            while (j + 1 < nums.size() && nums[j] == nums[j + 1])j++;
        }
        while (i + 1 < nums.size() && nums[i] == nums[i + 1])i++;
    }
    return ans;
}
ListNode* LeetFunc::removeNthFromEnd(ListNode* head, int n)
{
    ListNode *ans;
    ListNode *slow = head;
    ListNode *fast = head;
    for (int i = 0; i < n; i++)
        fast = fast->next;

    //avoid null pointer
    if (!fast)
    {
        ans = head->next;
        delete head;
        return ans;
    }

    while (fast->next)
    {
        slow = slow->next;
        fast = fast->next;
    }
    ListNode *del = slow->next;
    slow->next = slow->next->next;
    delete del;
    return head;
}
bool LeetFunc::isValid(std::string s)
{
    std::vector<char> check;
    for (char &c : s)
    {
        switch (c)
        {
        case '(':
        case '{':
        case '[':
            check.push_back(c);
            break;
        case ')':
            if (check.empty() || check.back() != '(') return false;
            else check.pop_back();
            break;
        case '}':
            if (check.empty() || check.back() != '{') return false;
            else check.pop_back();
            break;
        case ']':
            if (check.empty() || check.back() != '[') return false;
            else check.pop_back();
            break;
        default:
            break;
        }
    }
    return check.empty();
}
ListNode* LeetFunc::mergeTwoLists(ListNode* l1, ListNode* l2)
{
    ListNode ans(0);
    ListNode *p = &ans;

    while (l1 || l2)
    {
        if (!l1)
        {
            p->next = new ListNode(l2->val);
            p = p->next;
            l2 = l2->next;
        }
        else if (!l2)
        {
            p->next = new ListNode(l1->val);
            p = p->next;
            l1 = l1->next;
        }
        else if (l1->val < l2->val)
        {
            p->next = new ListNode(l1->val);
            p = p->next;
            l1 = l1->next;
        }
        else
        {
            p->next = new ListNode(l2->val);
            p = p->next;
            l2 = l2->next;
        }
    }
    return ans.next;
}
void LeetFunc::helper(std::string s, int left, int right)
{
    if (left == 0 && right == 0)
    {
        result.push_back(s);
        return;
    }

    if (left > 0)
    {
        helper(s + '(', left - 1, right + 1);
    }
    if (right > 0)
    {
        helper(s + ')', left, right - 1);
    }
}
std::vector<std::string> LeetFunc::generateParenthesis(int n)
{
    result.clear();
    helper("", n, 0);
    return result;
}
ListNode* LeetFunc::MergeTwoList(ListNode* L1, ListNode* L2)
{
    if (L1 == NULL)return L2;
    else if (L2 == NULL) return L1;
    else if (L1->val <= L2->val)
    {
        L1->next = MergeTwoList(L1->next, L2);
        return L1;
    }
    else
    {
        L2->next = MergeTwoList(L1, L2->next);
        return L2;
    }
}
ListNode* LeetFunc::mergeKLists(std::vector<ListNode*>& lists)
{
    if (lists.empty()) return nullptr;
    int Size = lists.size();
    while (Size>1)
    {
        for (int i = 0; i < Size / 2; i++)
        {
            lists[i] = MergeTwoList(lists[i], lists[Size - 1 - i]);
        }
        Size = (Size + 1) / 2;
    }
    return lists.front();
}
ListNode* LeetFunc::swapPairs(ListNode* head)
{
    ListNode **pp = &head, *a, *b;
    while ((a = *pp) && (b = a->next)) {
        a->next = b->next;
        b->next = a;
        *pp = b;
        pp = &(a->next);
    }
    return head;
}
ListNode* LeetFunc::reverseKGroup(ListNode* head, int k)
{
    ListNode *preheader = new ListNode(-1);
    preheader->next = head;
    ListNode *pre = preheader, *cur = preheader, *nex;

    int num = 0;
    while (cur = cur->next)num++;
    while (num>=k)
    {
        cur = pre->next;
        nex = cur->next;
        for (int i = 1; i < k; i++)
        {
            cur->next = nex->next;
            nex->next = pre->next;
            pre->next = nex;
            nex = cur->next;
        }
        pre = cur;
        num -= k;
    }
    return preheader->next;
}
int LeetFunc::longestValidParentheses(std::string s)
{
    std::stack<int> st;
    st.push(-1);
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')st.push(i);
        else if(s[i] == ')')
        {
            st.pop();
            if (st.empty())st.push(i);
            else
                ans = i - st.top() > ans ? i - st.top() : ans;
        }
    }
    return ans;
}
int LeetFunc::search(std::vector<int>& nums, int target)
{
    int l = 0, r = nums.size() - 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (nums[mid] == target)return mid;
        //5 6 7 1 2 3 4
        //l     m     r
        if (nums[l] > nums[mid])
        {
            if (nums[mid] < target && nums[r]>= target)l = mid + 1;
            else r = mid - 1;
        }
        //4 5 6 7 1 2 3
        //l     m     r
        else if(nums[mid] > nums[r])
        {
            if (nums[mid] > target && nums[l]<= target)r = mid - 1;
            else l = mid + 1;
        }
        //4 5 6 7 8 1 2 3
        //l   m   r
        else
        {
            if (nums[mid] < target)l = mid + 1;
            else r = mid - 1;
        }
    }
    return -1;
}
std::vector<int> LeetFunc::searchRange(std::vector<int>& nums, int target)
{
    std::vector<int> ans{-1,-1};
    if (nums.size() <= 0)return ans;

    int s = 0, e = nums.size() - 1;
    int l, mid, r;
    while (s<e)
    {
        mid = (s + e) / 2;
        if (nums[mid] < target)s = mid + 1;
        else e = mid;
    }
    if (nums[s] != target)return ans;
    else ans[0] = s;
    
    e = nums.size() - 1;
    while (s < e)
    {
        mid = (s + e) / 2 + 1;
        if (nums[mid] > target)e = mid - 1;
        else s = mid;
    }
    ans[1] = e;

    return ans;
}
int LeetFunc::searchInsert(std::vector<int>& nums, int target)
{
    int l = 0, r = nums.size() - 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (nums[mid] < target)l = mid + 1;
        else r = mid - 1;
    }
    return l;
}

bool LeetFunc::isValidSudoku(std::vector<std::vector<char>>& board)
{
    std::unordered_set<std::string> seen;
    seen.clear();
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            char num = board[i][j];
            if (num != '.')
            {
                std::stringstream s1;
                s1 << num << " in row " << i;
                std::stringstream s2;
                s2 << num << " in col " << j;
                std::stringstream s3;
                s3 << num << " in block " << i / 3 << " " << j / 3;
                if (!seen.insert(s1.str()).second ||
                    !seen.insert(s2.str()).second ||
                    !seen.insert(s3.str()).second)
                    return false;
            }
        }
    }
    return true;
}

bool LeetFunc::isValid(std::vector<std::vector<char>>& board, int row, int col, char value)
{
    for (int x = 0; x < 9; x++)if (board[row][x] == value) return false;
    for (int y = 0; y < 9; y++) if (board[y][col] == value)return false;
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (board[row / 3 * 3 + y][col / 3 * 3 + x] == value) return false;
        }
    }
    return true;
}

bool LeetFunc::solveSudoku(std::vector<std::vector<char>>& board, int row, int col)
{
    if (row == 9) return true;
    if (col == 9) return solveSudoku(board, row + 1, 0);
    if (board[row][col] != '.') return solveSudoku(board, row, col + 1);

    for (char c = '1'; c <= '9'; c++)
    {
        if (isValid(board, row, col, c))
        {
            board[row][col] = c;
            if (solveSudoku(board, row, col + 1))return true;
            else board[row][col] = '.';
        }
    }
    return false;
}

void LeetFunc::solveSudoku(std::vector<std::vector<char>>& board)
{
    solveSudoku(board, 0, 0);
}
