#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    int numSquares(int n)
    {
        queue<int> q;            //store all node prepare for del
        unordered_set<int> used; //store all the used nodes
        int setp = 0;
        q.push(n);
        used.insert(n);
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                int current = q.front();
                q.pop();

                if (current == 0)
                    return setp;
                cout << "current: " << current << endl;
                cout << "used set: ";
                for (auto local_it = used.begin(); local_it != used.end(); ++local_it)
                    std::cout << " " << *local_it;
                cout << endl;

                for (int j = 1; j * j <= current; j++)
                {
                    if (used.find(current - j * j) == used.end())
                    {
                        q.push(current - j * j);
                        used.insert(current - j * j);
                    }
                }
            }
            cout << "*************************************** \n";
            setp++;
        }
        return -1;
    }
};

int main(int argc, char const *argv[])
{
    int test_num = 12;
    Solution test;

    cout << "num of pingfangshu: " << test.numSquares(test_num) << endl;
    return 0;
}
