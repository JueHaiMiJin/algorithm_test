#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <unordered_set>


using namespace std;


class Solution
{
public:
    int openLock(vector<string> &deadends, string target)
    {
        //用来保存测试过的和会死锁的string
        unordered_set<string> m_set(deadends.begin(), deadends.end());

        //广度搜索时的队列
        queue<string> m_queue;

        //初始化，将初始的的条件添加进队列中
        string init_str("0000");
        m_queue.push(init_str);

        //判断初始状态是否存在deadline中
        if (m_set.find(init_str) != m_set.end())
        {
            return -1;
        }

        int res = 0;
        while (!m_queue.empty())
        {
            for (size_t i = 0; i < m_queue.size(); i++)
            {
                //从队列中取出第一个元素
                string tmp = m_queue.front();
                m_queue.pop();

                //判断是否既是终点
                if(tmp == target)
                    return res;

                m_set.emplace(tmp);
                for (size_t j = 0; j < 4; j++)
                {
                    for(size_t k = -1; k <= 1; k += 2 )
                    {
                        tmp[j] = ((tmp[j] - '0') + k + 10) %10 + 48;
                        if(m_set.find(tmp) != m_set.end())
                        {
                            m_queue.push(tmp);
                        }
                    }
                }
                res++;
            }
        }
        return -1;
    }
};

// [ "0201", "0101", "0102", "1212", "2002" ] 
// "0202"

int main(int argc, char const *argv[])
{
    vector<string> deadends = { "0201",
                                "0101",
                                "0102",
                                "1212",
                                "2002" };
    string target("0202");

    Solution test;
    cout << "ret " << test.openLock(deadends, target) << endl;

    return 0;
}
