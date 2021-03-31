
// Write an algorithm to determine if a number n is happy.

// A happy number is a number defined by the following process:

// Starting with any positive integer, replace the number by the sum of the squares of its digits.
// Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
// Those numbers for which this process ends in 1 are happy.

#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
    unordered_set<int> m_set;

public:
    bool isHappy(int n)
    {
        if (n == 1)
            return true;

        int tmp_num = 0;
        while (n)
        {
            tmp_num += ((n % 10) * (n % 10));
            n = n / 10;
        }
        if (m_set.count(tmp_num) > 0)
            return false;
        else
        {
            m_set.insert(tmp_num);
            return isHappy(tmp_num);
        }
    }
};