// Given two integer arrays nums1 and nums2, return an array of their intersection.
// Each element in the result must be unique and you may return the result in any order.

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

//双集合
class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> ret;
        unordered_set<int> m_set;
        unordered_set<int> ret_set;
        for (int i = 0; i < nums1.size(); i++)
            m_set.insert(nums1[i]);
        for (int i = 0; i < nums2.size(); i++)
        {
            if (m_set.count(nums2[i]) > 0)
            {
                ret_set.insert(nums2[i]);
            }
        }
        for (auto it = ret_set.begin(); it != ret_set.end(); it++)
            ret.push_back(*it);
        return ret;
    }
};

//双指针 效率高
class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        int pre = -1;
        vector<int> ret;
        int i = 0, j = 0;
        while (i < nums1.size() && j < nums2.size())
        {
            if (nums1[i] == nums2[j])
            {
                if (pre != nums1[i])
                {
                    ret.push_back(nums1[i]);
                    pre = nums1[i];
                }
                i++;
                j++;
            }
            else if (nums1[i] < nums2[j])
                i++;
            else if (nums1[i] > nums2[j])
                j++;
        }
        return ret;
    }
};