#include <iostream>
#include <vector>

using namespace std;

#if 0
class Solution
{
private:
public:
    int trap(vector<int> &height)
    {
        int len = height.size();
        int water_capacity = 0;
        int i = 0;
        int j = 0;
        for (i = 0; i < len;)
        {
            if (height[i] == 0)
            {
                i++;
                continue;
            }

            for (j = i + 2; j < len; j++)
            {
                if (height[i] <= height[j])
                {
                    water_capacity += height[i] * (j - i - 1) - (period_water(height, i + 1, j));
                    i = j;
                    break;
                }
            }

            if (i != j)
            {
                i++;
            }
        }
        return water_capacity;
    }
    int period_water(vector<int> &height, int start, int end)
    {
        int sum = 0;
        for (int i = start; i < end; i++)
        {
            sum += height[i];
        }
        return sum;
    }
};


class Solution
{
private:
public:
    int trap(vector<int> &height)
    {
        int len = height.size();
        int water_capacity = 0;
        int i = 0;
        int j = 0;
        for ( i = 0; i < len; )
        {
            cout << "Now i : " << i <<endl;
            if (height[i] == 0)
            {
                i++ ;
                continue;
            }

            int tmp_index = 0;
            for (j = i + 2; j < len; j++)
            {
                for (int k = j + 1; k < len; k++)
                {
                    if (height[k] > height[j])
                        tmp_index = k;
                }  
            }

            if (tmp_index > 0)
            {
                cout << " i " << i << " j " << j << endl;
                int tmp_height = (height[tmp_index] > height[i]) ? height[i] : height[tmp_index];
                int sum_capa = tmp_height * (tmp_height - i - 1);
                int no_water = period_water(height, i + 1, tmp_height);
                water_capacity += sum_capa - no_water;
                i = tmp_height;
                cout << "sum_capa: " << sum_capa << " no_water: " << no_water << " water_capacity: " << water_capacity << endl;
            }
            else
            {
                i++;
            }
            
                
            // if (i != tmp_height)
            // {
            //     i++;
            // }
        }

        return water_capacity;
    }

    int period_water(vector<int> &height, int start, int end)
    {
        int sum = 0;
        for (int i = start; i < end; i++)
        {
            sum += height[i];
        }
        return sum;
    }
};
#endif

class Solution
{
private:
public:
    int trap(vector<int> &height)
    {
        #if 0 
        //暴力方式
        int ans = 0;
        for(int i = 1; i < height.size() -1; i++)
        {
            int Lmax = 0;
            int Rmax = 0;

            for (int  j = i; j > 0 ; j--)
            {
                Lmax = max(Lmax, height[j]);
            }

            for (int k = i; k < height.size(); k++)
            {
                Rmax = max(Rmax, height[k]);
            }

            ans += min(Lmax, Rmax) - height[i];
        }

        return ans;
        #endif

#if 0
        //动态规划
        if(height.empty() || height.size() < 3)
        return 0;

        int ans = 0;
        int len = height.size();
        vector<int> left_max(len), right_max(len);
        left_max[0] = height[0];
        right_max[len-1] = height[len -1]; 

        //从左向右查询最大高度
        for (int i = 1; i < len; i++)
        {
            left_max[i] = max(left_max[i-1], height[i]);
        }

        //从右向左查询最大高度
        for (int i = len -2; i > 0; i--)
        {
            right_max[i] = max(right_max[i + 1], height[i]);
        }

        //使用两边最大高度较小的一个作为水量高度减去当前的位置高度作为当前位置的储水容量
        for (int i = 1; i < len -1; i++)
        {
            ans += min(left_max[i], right_max[i]) - height[i];
        }

        return ans;
#endif

        //使用双指针
        int ans = 0;
        int left = 0, right = height.size() -1;
        int left_max = 0, right_max = 0;
        while (left < right)
        {
            if(height[left] < height[right])
            {
                if (left_max < height[left])
                {
                    left_max = height[left];
                    left++;
                }
                else
                {
                    ans += left_max - height[left];
                    cout << "lans: " << ans << endl;
                    left++;
                }
            }
            else
            {
                if (right_max < height[right])
                {
                    right_max = height[right];
                    right--;
                }
                else
                {
                    ans += right_max - height[right];
                    cout << "rans: " << ans << endl;
                    right--;
                }
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[])
{
    //[ 4, 2, 0, 3, 2, 5 ]
    //[0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
    vector<int> height = {4, 2, 0, 3, 2, 5};
    Solution tt;
    cout << "capacity " << tt.trap(height) << endl;
    return 0;
}
