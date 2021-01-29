#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


//这个方法是有问题的，[3,3]返回的是[1,1]应该返回[0,1];
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> tmp_map;
        for (int i = 0; i < nums.size(); i++)
        {
            tmp_map[nums[i]] = i;
        }

        sort(nums.begin(), nums.end());
        int left = 0;
        int right = nums.size() - 1;
        vector<int> ret;
        while (left < right)
        {
            if ((nums[left] + nums[right]) == target)
            {

                ret.push_back(tmp_map[nums[left]]);
                ret.push_back(tmp_map[nums[right]]);
                break;
            }
            else if ((nums[left] + nums[right]) > target)
                right--;
            else
                left++;
        }
        return ret;
    }
};