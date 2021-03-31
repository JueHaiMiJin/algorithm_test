// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

// You may assume that each input would have exactly one solution,
// and you may not use the same element twice.

// You can return the answer in any order.

#include <iostream>
#include <unordered_set>

using namespace std;

class Solution
{
    unordered_map<int, int> m_map;

public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            auto it = m_map.find(target - nums[i]);
            if (it != m_map.end())
                return {it->second, i};
            else
                m_map[nums[i]] = i;
        }
        return {};
    }
};