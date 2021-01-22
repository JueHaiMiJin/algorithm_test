#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>



using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {
        if (s.length() % 2 || s.length() == 0)
            return false;

        unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };

        stack<char> m_stack;

        for(char ch:s)
        {
            if(pairs.count(ch))
            {
                if(m_stack.empty() || m_stack.top() != pairs[ch])
                    return false;
                else
                {
                    m_stack.pop();
                }
                
            }
            else
            {
                m_stack.push(ch);
            }
        }
        return m_stack.empty();
    }
};


int main(int argc, char const *argv[])
{
    string str("([{[}]])");
    Solution test;
    cout << "result: " << test.isValid(str) << endl;
    return 0;
}
