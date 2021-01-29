// 给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。
// 进阶：
//     尽可能想出更多的解决方案，至少有三种不同的方法可以解决这个问题。 你可以使用空间复杂度为 O(1) 的 原地 算法解决这个问题吗？

class Solution
{
public:
    void rt(vector<int> &nums)
    {
        int tmp_num = nums.back();
        nums.pop_back();
        nums.insert(nums.begin(), tmp_num);
    }
    void rotate(vector<int> &nums, int k)
    {
        for (int i = 1; i <= k; i++)
        {
            rt(nums);
        }
    }
};


