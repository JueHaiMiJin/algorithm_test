#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct Node{
    int level;
    int value;
};

class digui{
public:
    vector<int> m_vect;
public:
    digui();
    ~digui();
public:
    void diguidiaoyong(std::list<Node> &m_list, auto left, auto right)
    {
        m_vect.push_back(left->value);
        if(left == right)
            return;
            
        auto it_tmp = left;
        for (it_tmp != m_list.end(); it_tmp++)
        {
            if (it_tmp->level == left->level)
            {
                diguidiaoyong(m_list, left, --it_tmp);
                break;
            }
        }
        if (it_tmp != m_list.end())
            diguidiaoyong(m_list, it_tmp, right);
        else
            diguidiaoyong(m_list, ++left, right);
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
