#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int area_tmp = 0;
//深度优先
class Solution
{
public:
    Solution()
    {
        island_num = 0;
        island_max_area = 0;
    }

private:
    void find(vector<vector<char>> &grid, int r, int d)
    {
        int m = grid.size();
        int n = grid[0].size();

        area_tmp++;
        grid[r][d] = '0';
        if (((r - 1) >= 0) && (grid[r - 1][d] == '1'))
            find(grid, r - 1, d);
        if ((r + 1) < m && (grid[r + 1][d] == '1'))
            find(grid, r + 1, d);
        if (((d - 1) >= 0) && (grid[r][d - 1] == '1'))
            find(grid, r, d - 1);
        if (((d + 1) < n) && (grid[r][d + 1] == '1'))
            find(grid, r, d + 1);
    }

public:
    int numIslands(vector<vector<char>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        cout << "nr: " << m << endl;
        cout << "dr: " << n << endl;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == '1')
                {
                    //进行查找
                    cout << "find i: " << i << " j:" << j << endl;
                    find(grid, i, j);
                    island_num++;
                    island_max_area = island_max_area > area_tmp ? island_max_area : area_tmp;
                    area_tmp = 0;
                }
            }
        }
        return island_num;
    }

    int getmaxislandarea()
    {
        return island_max_area;
    }

private:
    int island_num;
    int island_max_area;
};

#if 0
//广度优先
class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int nr = grid.size();
        if (!nr)
            return 0;
        int nc = grid[0].size();

        int num_islands = 0;
        for (int r = 0; r < nr; ++r)
        {
            for (int c = 0; c < nc; ++c)
            {
                if (grid[r][c] == '1')
                {
                    ++num_islands;
                    grid[r][c] = '0';
                    queue<pair<int, int>> neighbors;
                    neighbors.push({r, c});
                    while (!neighbors.empty())
                    {
                        auto rc = neighbors.front();
                        neighbors.pop();
                        int row = rc.first, col = rc.second;
                        if (row - 1 >= 0 && grid[row - 1][col] == '1')
                        {
                            neighbors.push({row - 1, col});
                            grid[row - 1][col] = '0';
                        }
                        if (row + 1 < nr && grid[row + 1][col] == '1')
                        {
                            neighbors.push({row + 1, col});
                            grid[row + 1][col] = '0';
                        }
                        if (col - 1 >= 0 && grid[row][col - 1] == '1')
                        {
                            neighbors.push({row, col - 1});
                            grid[row][col - 1] = '0';
                        }
                        if (col + 1 < nc && grid[row][col + 1] == '1')
                        {
                            neighbors.push({row, col + 1});
                            grid[row][col + 1] = '0';
                        }
                    }
                }
            }
        }

        return num_islands;
    }
};
#endif

/* [ [ "1", "1", "0", "0", "0" ], [ "1", "1", "0", "0", "0" ], [ "0", "0", "1", "0", "0" ], [ "0", "0", "0", "1", "1" ] ] */

int main(int argc, char const *argv[])
{
    vector<vector<char>> grid = {{'1', '1', '0', '0', '0'},
                                 {'1', '1', '0', '0', '0'},
                                 {'0', '0', '1', '0', '0'},
                                 {'1', '0', '0', '1', '1'},
                                 {'1', '0', '1', '0', '1'}};

    // vector<vector<char>> grid = {{'1', '1', '1'},
    //                              {'0', '1', '0'},
    //                              {'1', '1', '1'}};

    Solution m_sloution;
    int ret = m_sloution.numIslands(grid);
    cout << "island num: " << ret << endl;
    cout << "max islandare: " << m_sloution.getmaxislandarea() << endl;
    return 0;
}

#if 0
//并查集
class UnionFind
{
public:
    UnionFind(vector<vector<char>> &grid)
    {
        count = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == '1')
                {
                    parent.push_back(i * n + j);
                    ++count;
                }
                else
                {
                    parent.push_back(-1);
                }
                rank.push_back(0);
            }
        }
    }

    int find(int i)
    {
        if (parent[i] != i)
        {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    void unite(int x, int y)
    {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty)
        {
            if (rank[rootx] < rank[rooty])
            {
                swap(rootx, rooty);
            }
            parent[rooty] = rootx;
            if (rank[rootx] == rank[rooty])
                rank[rootx] += 1;
            --count;
        }
    }

    int getCount() const
    {
        return count;
    }

private:
    vector<int> parent;
    vector<int> rank;
    int count;
};

class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int nr = grid.size();
        if (!nr)
            return 0;
        int nc = grid[0].size();

        UnionFind uf(grid);
        int num_islands = 0;
        for (int r = 0; r < nr; ++r)
        {
            for (int c = 0; c < nc; ++c)
            {
                if (grid[r][c] == '1')
                {
                    grid[r][c] = '0';
                    if (r - 1 >= 0 && grid[r - 1][c] == '1')
                        uf.unite(r * nc + c, (r - 1) * nc + c);
                    if (r + 1 < nr && grid[r + 1][c] == '1')
                        uf.unite(r * nc + c, (r + 1) * nc + c);
                    if (c - 1 >= 0 && grid[r][c - 1] == '1')
                        uf.unite(r * nc + c, r * nc + c - 1);
                    if (c + 1 < nc && grid[r][c + 1] == '1')
                        uf.unite(r * nc + c, r * nc + c + 1);
                }
            }
        }

        return uf.getCount();
    }
};
#endif
