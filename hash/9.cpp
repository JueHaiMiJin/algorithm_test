// 给定一个由若干 0 和 1 组成的数组 A，我们最多可以将 K 个值从 0 变成 1 。

// 返回仅包含 1 的最长（连续）子数组的长度。


class Solution
{
public:
    int longestOnes(vector<int> &A, int K)
    {
        vector<int> tmp_vect;
        int len = A.size();
        int i = 0, j = 0, k = 1;
        int num_zero = 0;
        int ret_len = 0;
        while (j < len)
        {
            if (A[j] == 0)
                ++num_zero;
            if (num_zero > K)
            {
                ret_len = max(ret_len, j - i);
                if (A[i++] == 0)
                    --num_zero;
            }
            ++j;
        }
        ret_len = max(ret_len, j - i);
        return ret_len;
    }
};