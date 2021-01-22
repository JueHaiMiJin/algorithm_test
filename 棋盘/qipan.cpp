#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>


using namespace std;

typedef struct Position{
    int x;
    int y;
}Position;

#if 0
//深度优先
class Solution
{
private:
    int step;

public:
    void diguixunlu(Position &m_pos)
    {
        if(m_pos.x == 8 && m_pos.y == 8 )
        {
            return;
        }
        else
        {
            step++;
            if ((m_pos.x + 2) <= 8)
            {
                if ((m_pos.y + 1) <= 8) 
                {
                    m_pos.x += 2;
                    m_pos.y += 1;
                    diguixunlu(m_pos);
                }
                
                if ((m_pos.y - 1) >= 0)
                {
                    m_pos.x += 2;
                    m_pos.y -= 1;
                    diguixunlu(m_pos);
                } 
            }

            if ((m_pos.x - 2) >= 0)
            {
                if ((m_pos.y + 1) <= 8)
                {
                    m_pos.x -= 2;
                    m_pos.y += 1;
                    diguixunlu(m_pos);
                } 
                if ((m_pos.y - 1) >= 0)
                {
                    m_pos.x -= 2;
                    m_pos.y -= 1;
                    diguixunlu(m_pos);
                } 
            }

            if ((m_pos.y - 2) >= 0)
            {
                if ((m_pos.x + 1) <= 8)
                {
                    m_pos.y -= 2;
                    m_pos.x += 1;
                    diguixunlu(m_pos);
                }
                if ((m_pos.x - 1) >= 0)
                {
                    m_pos.y -= 2;
                    m_pos.x -= 1;
                    diguixunlu(m_pos);
                }
            }

            if ((m_pos.y + 2) <= 8)
            {
                if ((m_pos.x + 1) <= 8)
                {
                    m_pos.y += 2;
                    m_pos.x += 1;
                    diguixunlu(m_pos);
                }
                if ((m_pos.x - 1) >= 0)
                {
                    m_pos.y += 2;
                    m_pos.x -= 1;
                    diguixunlu(m_pos);
                }
            }
        }
        
    }
    int trap(Position &pos)
    {
        step = 0;
        diguixunlu(pos);
        return step;
    }
    
};
#endif

    //广度优先
    class Solution
    {
    private:
        int step;

    public:
        int trap(Position &pos)
        {
            step = 0;
            queue<Position> q;
            //unordered_set<Position> used;

            q.push(pos);
            //used.insert(pos);

            while (!q.empty())
            {
                int size = q.size();
                for (int i = 0; i < size; i++)
                {
                    Position tmp = q.front();
                    q.pop();

                    // if (used.count(tmp) <= 0)
                    // {
                    //     used.insert(tmp);
                    // }

                    if (((tmp.x + 2) <= 8 && (tmp.y + 1) <= 8))
                    {
                        Position m_tmp = {tmp.x + 2,
                                          tmp.y + 1};
                        //used.insert(m_tmp);
                        q.push(m_tmp);
                    }

                    if (((tmp.x + 2) <= 8 && (tmp.y - 1) >= 0))
                    {
                        Position m_tmp = {tmp.x + 2,
                                          tmp.y - 1};
                        //used.insert(m_tmp);
                        q.push(m_tmp);
                    }

                    if (((tmp.x - 2) >= 0 && (tmp.y + 1) <= 8))
                    {
                        Position m_tmp = {tmp.x - 2,
                                          tmp.y + 1};
                        //used.insert(m_tmp);
                        q.push(m_tmp);
                    }

                    if (((tmp.x - 2) >= 0 && (tmp.y - 1) >= 0))
                    {
                        Position m_tmp = {tmp.x - 2,
                                          tmp.y - 1};
                        //used.insert(m_tmp);
                        q.push(m_tmp);
                    }

                    if (((tmp.y - 2) >= 0 && (tmp.x + 1) <= 8))
                    {
                        Position m_tmp = {tmp.x + 1,
                                          tmp.y - 2};
                        //used.insert(m_tmp);
                        q.push(m_tmp);
                    }

                    if (((tmp.y - 2) >= 0 && (tmp.x - 1) >= 0))
                    {
                        Position m_tmp = {tmp.x - 1,
                                          tmp.y - 2};
                        //used.insert(m_tmp);
                        q.push(m_tmp);
                    }

                    if (((tmp.y + 2) <= 8 && (tmp.x + 1) <= 8))
                    {
                        Position m_tmp = {tmp.x + 1,
                                          tmp.y + 2};
                        //used.insert(m_tmp);
                        q.push(m_tmp);
                    }

                    if (((tmp.y + 2) <= 8 && (tmp.x - 1) >= 0))
                    {
                        Position m_tmp = {tmp.x - 1,
                                          tmp.y + 2};
                        //used.insert(m_tmp);
                        q.push(m_tmp);
                    }
                }
                step++;
            }
            return step;
        }
    };

    int main(int argc, char const *argv[])
    {
        Solution test;
        Position tt = {0, 0};
        int step = test.trap(tt);
        cout << "step num : " << step << endl;
        return 0;
    }
