// Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.

// Follow up: Could you implement a solution with a linear runtime complexity and without using extra memory?

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        if (nums.size() < 2)
            return nums[0];
        sort(nums.begin(), nums.end());
        if (nums[0] != nums[1])
            return nums[0];
        for (int i = 2; i <= nums.size() - 1;)
        {
            if ((i + 1) > (nums.size() - 1))
                return nums[i];
            if (nums[i] != nums[i + 1])
            {
                return nums[i];
            }
            else
            {
                i += 2;
            }
        }
        return 0;
    }
};