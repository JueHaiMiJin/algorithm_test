// 给定一个整数数组和一个整数 k，判断数组中是否存在两个不同的索引 i 和 j，使得 nums[i] = nums[j] ，并且 i 和 j 的差的 绝对值 至多为 k。


class Solution
{
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> m_map;
        for (int i = 0; i < nums.size(); i++)
        {
            if (m_map.count(nums[i]) > 0)
            {
                if (i - m_map[nums[i]] <= k)
                    return true;
                else
                    m_map[nums[i]] = i;
            }
            else
            {
                m_map[nums[i]] = i;
            }
        }
        return false;
    }
};