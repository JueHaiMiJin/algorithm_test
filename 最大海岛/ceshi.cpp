#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class Solution
{
public:
    int digui(vector<vector<int> > &grid, int x, int y)
    {
        int ret = 1;
        grid[x][y] = 0;
        //cout << "[" << x << "," << y << "]" << " grid: " << grid[x][y] << endl;
        if ((x - 1) >= 0 && grid[x - 1][y] == 1)
            ret += digui(grid, x - 1, y);
        if ((x + 1) < grid.size() && grid[x + 1][y] == 1)
            ret += digui(grid, x + 1, y);
        if ((y - 1) >= 0 && grid[x][y - 1] == 1)
            ret += digui(grid, x, y - 1);
        if ((y + 1) < grid[0].size() && grid[x][y + 1] == 1)
            ret += digui(grid, x, y + 1);
        return ret;
    }

    int maxAreaOfIsland(vector<vector<int> > &grid)
    {
        vector<int> m_ret;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j])
                {
                    int ret = digui(grid, i, j);
                    //cout << "ret : " << ret <<endl;
                    m_ret.push_back(ret);
                }
                    
            }
        }

        sort(m_ret.begin(), m_ret.end(), [](int a, int b) { return a > b; });
        return m_ret.front();
    }
};

int main()
{

    srand((unsigned)time(NULL));
    vector<vector<int> > grid = {{1, 1, 0, 0, 0},
                                {1, 1, 0, 0, 0},
                                {0, 0, 0, 1, 1},
                                {0, 0, 0, 1, 1}};

    vector<vector<int> > tmp_grid;
    int height = rand() % 50 + 1;
    int width = rand()%50 + 1;
    cout << "height " << height << " width" << width << endl;

    for (int i = 0; i < width; i++) 
    {
        vector<int> tmp_vect;
        for (int j = 0; j < height; j++)
        {
            int tmp = rand() % 2;
            tmp_vect.push_back(tmp);
            //cout << "tmp num " << tmp << endl;
        }
        tmp_grid.push_back(tmp_vect);
        for(int k = 0; k < height; k++)
            cout << tmp_vect[k] << ", ";
        cout << endl;
    }
        
            
    Solution s;
    int ret = s.maxAreaOfIsland(tmp_grid);
    cout  << "ret " << ret <<endl;
     return 0;
}