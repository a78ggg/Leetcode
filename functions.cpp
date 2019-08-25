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
    //step1. 從cur item找對應的target
    //if 找到->return ans
    //else-> cur item丟進map中

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
    //當前值 = (list1+list2)%10 + 前次進位值
    //進位值 = (list1+list2)/10

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
    //將字元和對應index放入map
    //字串長度為 : 當前id - 前次重複id

    int maxSize = 0;
    int curIndex = -1;
    std::unordered_map<char, int> map;
    for (int i = 0; i < s.size(); i++)
    {
        char word = s[i];
        std::unordered_map<char, int>::iterator iter = map.find(word);
        if (iter != map.end())
        {
            curIndex = std::max(curIndex, iter->second);
        }
        map[word] = i;
        maxSize = std::max(maxSize, i - curIndex);
    }
    return maxSize;
}
double LeetFunc::findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
{
    //step1 先算出迴圈次數 times = (v1.size()+v2.size())/2+1
    //if v1 reach end ---> v2++
    //if v2 reach end ---> v1++
    //if v1.next < v2.next ---> v1++
    //if v2.next < v1.next ---> v2++
    //return ans = (v1[cur]+v2[cur])/2

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
    //step 找到mid 向左向右展開

    if (s.size() <= 1)return s;

    int maxLength = 0;
    int maxLeft = 0;
    for (int mid = 0; mid < s.size();)
    {
        int left = mid;
        int right = mid;

        //重複字元不用計算
        while (right < s.size() && s[right] == s[right + 1])right++;
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
    //123--->321
    //-123--->-321

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
    //step1 int->string
    //step2 檢查對稱

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
    //找左右邊界圍成最大面積
    //if 左邊界高度<=cur高度 左++
    //if 右邊界高度<=cur高度 右--

    int maxA = 0;
    int l = 0, r = height.size() - 1;
    while (l < r)
    {
        int h = std::min(height[l], height[r]);
        maxA = std::max(maxA, h*(r - l));
        while (height[l] <= h && l < r)l++;
        while (height[r] <= h && l < r)r--;
    }
    return maxA;
}
std::string LeetFunc::longestCommonPrefix(std::vector<std::string>& strs)
{
    //step1 取strs[0]作為base
    //探索各個string與base重複的長度

    if (strs.size() <= 0)return "";

    std::string base = strs.at(0);
    size_t r = base.size();
    for (int i = 1; i < strs.size(); i++)
    {
        std::string cur = strs.at(i);
        int l = 0;
        r = std::min(r, cur.size());
        while (base[l] == cur[l] && l < r)l++;
        r = l;
    }
    return base.substr(0, r);
}
std::vector<std::vector<int>> LeetFunc::threeSum(std::vector<int>& nums)
{
    //cur + target = 0
    //target = left + right

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
    // ans = cur + (left + right)

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
    //map<數字,對應英文字母>
    //letters以for迴圈push_back加入

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
            int tarValue = target - (nums[i] + nums[j]);

            int s = j + 1, e = nums.size() - 1;
            while (s < e)
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
    //fast先位移n次，接著slow,fast同時平移至fast.end()
    //移除slow所在位置

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
    while (Size > 1)
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
    while (num >= k)
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
        else if (s[i] == ')')
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
            if (nums[mid] < target && nums[r] >= target)l = mid + 1;
            else r = mid - 1;
        }
        //4 5 6 7 1 2 3
        //l     m     r
        else if (nums[mid] > nums[r])
        {
            if (nums[mid] > target && nums[l] <= target)r = mid - 1;
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
    std::vector<int> ans{ -1,-1 };
    if (nums.size() <= 0)return ans;

    int s = 0, e = nums.size() - 1;
    int l, mid, r;
    while (s < e)
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

void LeetFunc::combinationSum(std::vector<int>& candidates, int target, std::vector<std::vector<int>>& vvans, std::vector<int>& vsum, int left)
{
    if (target == 0)
    {
        vvans.push_back(vsum);
        return;
    }

    for (int i = left; i < candidates.size() && target >= candidates[i]; i++)
    {
        vsum.push_back(candidates[i]);
        combinationSum(candidates, target - candidates[i], vvans, vsum, i);
        vsum.pop_back();
    }
}

std::vector<std::vector<int>> LeetFunc::combinationSum(std::vector<int>& candidates, int target)
{
    std::sort(candidates.begin(), candidates.end());
    std::vector<std::vector<int>> vvans;
    std::vector<int> vsum;
    combinationSum(candidates, target, vvans, vsum, 0);
    return vvans;
}

void LeetFunc::combinationSum2(std::vector<int>& candidates, int target, std::vector<std::vector<int>> &vvans, std::vector<int> &vsum, int left)
{
    if (target == 0)
    {
        vvans.push_back(vsum);
        return;
    }

    for (int i = left; i < candidates.size() && target >= candidates[i]; i++)
    {
        if (i && candidates[i] == candidates[i - 1] && i > left)continue;
        vsum.push_back(candidates[i]);
        combinationSum2(candidates, target - candidates[i], vvans, vsum, i + 1);
        vsum.pop_back();
    }
}

std::vector<std::vector<int>> LeetFunc::combinationSum2(std::vector<int>& candidates, int target)
{
    std::sort(candidates.begin(), candidates.end());
    std::vector<std::vector<int>> vvans;
    std::vector<int> vsum;
    combinationSum2(candidates, target, vvans, vsum, 0);
    return vvans;
}

int LeetFunc::firstMissingPositive(std::vector<int>& nums)
{
    int ans = 1;
    std::sort(nums.begin(), nums.end());
    std::unordered_set<int> added;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] < 1)continue;
        if (!added.insert(nums[i]).second) continue;
        if (nums[i] == ans)ans++;
        else return ans;
    }
    return ans;
}

int LeetFunc::trap(std::vector<int>& height)
{
    int sum = 0;
    int left = 0, right = height.size() - 1;
    int l_wall = 0, r_wall = 0;
    while (left <= right)
    {
        if (height[left] <= height[right])
        {
            if (height[left] >= l_wall) l_wall = height[left];
            else sum += l_wall - height[left];
            left++;
        }
        else
        {
            if (height[right] >= r_wall) r_wall = height[right];
            else sum += r_wall - height[right];
            right--;
        }
    }
    return sum;
}

bool LeetFunc::isMatch(std::string s, std::string p)
{
    int size_s = s.size(), size_p = p.size();
    int i = 0, j = 0, p_restart = -1, s_match;
    while (i < size_s)
    {
        if (j < size_p && p[j] == '*')
        {
            s_match = i;
            p_restart = j++;
        }
        else if (j < size_p && (s[i] == p[j] || p[j] == '?'))
        {
            i++;
            j++;
        }
        else if (p_restart >= 0)
        {
            s_match++;
            i = s_match;
            j = p_restart + 1;
        }
        else return false;
    }
    while (j < size_p && p[j] == '*')j++;
    return j == size_p;
}

int LeetFunc::jump(std::vector<int>& nums)
{
    int i = 0, n = nums.size(), step = 0, end = 0, maxend = 0;
    while (end < n - 1) {
        step++;
        for (; i <= end; i++) {
            maxend = std::max(maxend, i + nums[i]);
            if (maxend >= n - 1) return step;
        }
        if (end == maxend) break;
        end = maxend;
    }
    return n == 1 ? 0 : -1;
}

void LeetFunc::permute(std::vector<int>& nums, int begin, std::vector<std::vector<int>>& vvans)
{
    if (begin == nums.size())
    {
        vvans.push_back(nums);
        return;
    }

    for (int i = begin; i < nums.size(); i++)
    {
        if (nums[i] != nums[begin])
            std::swap(nums[begin], nums[i]);
        permute(nums, begin + 1, vvans);
        std::swap(nums[begin], nums[i]);
    }
}

std::vector<std::vector<int>> LeetFunc::permute(std::vector<int>& nums)
{
    std::vector<std::vector<int>> vvans;
    permute(nums, 0, vvans);
    return vvans;
}

void LeetFunc::permuteUnique(std::vector<int> nums, int pos, std::vector<std::vector<int>>& vvans)
{
    int vsize = nums.size();
    if (pos == vsize)
    {
        vvans.push_back(nums);
        return;
    }

    for (int i = pos; i < vsize; ++i)
    {
        if (i != pos && nums[i] == nums[pos])continue;
        std::swap(nums[pos], nums[i]);
        permuteUnique(nums, pos + 1, vvans);
    }
}

std::vector<std::vector<int>> LeetFunc::permuteUnique(std::vector<int>& nums)
{
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> vvans;
    permuteUnique(nums, 0, vvans);
    return vvans;
}

void LeetFunc::rotate(std::vector<std::vector<int>>& matrix)
{
    //step1 上下反轉
    //step2 鏡像交換
    std::reverse(matrix.begin(), matrix.end());
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = i + 1; j < matrix[i].size(); j++)
        {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
}

std::vector<std::vector<std::string>> LeetFunc::groupAnagrams(std::vector<std::string>& strs)
{
    //建立unordered_map<排序後string,vector<string>>
    //分別輸出vector<string>

    std::vector<std::vector<std::string>> vv_ans;

    std::unordered_map<std::string, std::vector<std::string>> map;
    for (std::string &str : strs)
    {
        std::string curStr = str;
        std::sort(curStr.begin(), curStr.end());
        map[curStr].push_back(str);
    }

    for (auto &id : map)
    {
        vv_ans.push_back(id.second);
    }
    return vv_ans;
}

int LeetFunc::maxSubArray(std::vector<int>& nums)
{
    //累加curSum
    //存入AnsSum

    int curSum = 0;
    int AnsSum = INT_MIN;
    for (int i = 0; i < nums.size(); i++)
    {
        curSum = std::max(nums[i], curSum + nums[i]);
        AnsSum = std::max(AnsSum, curSum);
    }
    return AnsSum;
}

bool LeetFunc::canJump(std::vector<int>& nums)
{
    if (nums.size() == 1)return true;
    int i = 0, n = nums.size(), curEnd = 0, maxEnd = 0;
    while (curEnd < n - 1)
    {
        for (; i <= curEnd; i++)
        {
            maxEnd = std::max(maxEnd, i + nums[i]);
            if (maxEnd >= n - 1)return true;
        }
        if (curEnd == maxEnd)break;
        curEnd = maxEnd;
    }
    return false;
}

std::vector<std::vector<int>> LeetFunc::merge(std::vector<std::vector<int>>& intervals)
{
    // current (A,B)  ans(C,D)
    // if A>D || B<C : no overlap -->ans.puch_back(current)
    // else : new boundary = (min(A,C),max(B,D))

    std::vector<std::vector<int>> vvans;
    std::sort(intervals.begin(), intervals.end());

    for (std::vector<int> &vcur : intervals)
    {
        bool isMerged = false;
        for (std::vector<int> &vans : vvans)
        {
            if (vcur[0] > vans[1] || vcur[1] < vans[0])continue;
            else
            {
                vans[0] = std::min(vcur[0], vans[0]);
                vans[1] = std::max(vcur[1], vans[1]);
                isMerged = true;
            }
        }
        if (!isMerged)
        {
            vvans.push_back(vcur);
        }
    }

    return vvans;
}

std::vector<std::vector<int>> LeetFunc::insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval)
{
    if (intervals.size() == 0) return { newInterval };
    auto compare = [](const std::vector<int>&intv1, const std::vector<int>&intv2)
    { return intv1[1] < intv2[0]; };
    auto range = std::equal_range(intervals.begin(), intervals.end(), newInterval, compare);
    auto itr1 = range.first, itr2 = range.second;
    if (itr1 == itr2) {
        intervals.insert(itr1, newInterval);
    }
    else {
        itr2--;
        *(itr2->begin() + 0) = std::min(newInterval[0], *(itr1->begin() + 0));
        *(itr2->begin() + 1) = std::max(newInterval[1], *(itr2->begin() + 1));
        intervals.erase(itr1, itr2);
    }
    return intervals;
}

void LeetFunc::getPermutation(std::string & s_input, std::string & s_ans, int index, int target)
{
    if (s_ans != "")return;
    if (m_count == target)
    {
        s_ans = s_input;
    }

    for (int i = index; i < s_input.size(); i++)
    {
        std::swap(s_input[i], s_input[index]);
        m_count = i == index ? m_count : m_count + 1;
        getPermutation(s_input, s_ans, index + 1, target);
        std::swap(s_input[i], s_input[index]);
    }
}

std::string LeetFunc::getPermutation(int n, int k)
{
    m_count = 1;
    int num = 1;
    std::string s_ans = "";
    std::string s_input = "";
    std::stringstream ss;
    while (num <= n)
        ss << num++;

    s_input = ss.str();
    int count = 0;
    getPermutation(s_input, s_ans, 0, k);

    return s_ans;
}

int LeetFunc::uniquePaths(int m, int n)
{
    if (m < 1 || n < 1)return 0;

    std::vector<std::vector<int>> vv_ans(m, std::vector<int>(n, 1));
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            vv_ans[i][j] = vv_ans[i - 1][j] + vv_ans[i][j - 1];
        }
    }
    return vv_ans[m - 1][n - 1];
}

int LeetFunc::uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid)
{
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    std::vector<std::vector<long long>> vv_ans(m + 1, std::vector<long long>(n + 1, 0));
    vv_ans[0][1] = 1;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (!obstacleGrid[i-1][j-1])
            {
                vv_ans[i][j] = vv_ans[i - 1][j] + vv_ans[i][j - 1];
            }
        }
    }
    return vv_ans[m][n];
}

int LeetFunc::minPathSum(std::vector<std::vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();
    for (int i = 1; i < n; i++)
    {
        grid[0][i] += grid[0][i - 1];
    }
    for (int j = 1; j < m; j++)
    {
        grid[j][0] += grid[j - 1][0];
    }
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            grid[i][j] = grid[i][j] + std::min(grid[i][j - 1], grid[i - 1][j]);
        }
    }
    return grid[m - 1][n - 1];
}

std::string LeetFunc::addBinary(std::string a, std::string b)
{
    int m = a.size() - 1, n = b.size() - 1, sum = 0;
    std::string ans;

    while (sum > 0 || m >= 0 || n >= 0)
    {
        sum += (m >= 0 ? a[m--] - '0' : 0) + (n >= 0 ? b[n--] - '0' : 0);
        ans = char(sum % 2 + '0') + ans;
        sum /= 2;
    }
    return ans;
}

int LeetFunc::climbStairs(int n)
{
    std::vector<int> v_ans(n, 0);
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    v_ans[0] = 1;
    v_ans[1] = 2;
    for (int i = 2; i < n; i++)
    {
        v_ans[i] = v_ans[i - 1] + v_ans[i - 2];
    }
    return v_ans[n - 1];
}

int LeetFunc::minDistance(std::string word1, std::string word2)
{
    /* Edit Distance
     * 解說:https://www.ptt.cc/bbs/Grad-ProbAsk/M.1470239320.A.268.html
     */
    int m = word1.size();
    int n = word2.size();

    std::vector<std::vector<int>> vv_dpans(m + 1, std::vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++)
    {
        vv_dpans[i][0] = i;
    }
    for (int j = 0; j <= n; j++)
    {
        vv_dpans[0][j] = j;
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (word1[i - 1] == word2[j - 1])
                vv_dpans[i][j] = vv_dpans[i - 1][j - 1];
            else
                vv_dpans[i][j] = std::min(vv_dpans[i - 1][j - 1], std::min(vv_dpans[i][j - 1], vv_dpans[i - 1][j])) + 1;
        }
    }
    return vv_dpans[m][n];

    return 0;
}
