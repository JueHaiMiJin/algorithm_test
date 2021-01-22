#include <iostream>
#include <string>
#include <vector>
#include <stack>


using namespace std;

class Solution
{
public:
    int evalRPN(vector<string> &tokens)
    {
        stack<string> m_str;
        stack<int> m_num;
        for (int i = 0; i < tokens.size(); i++)
        {
            // cout << "count " << i << endl;
            // cout << "tokens[i] " << tokens[i] <<endl;
            if ((tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") && m_num.size() > 1 && m_str.size() >1)
            {
                cout << "size " << m_num.size() <<endl;
                string str = "(";
                string m_str1 = m_str.top();
                m_str.pop();
                string m_str2 = m_str.top();
                m_str.pop();
                str += m_str2 + tokens[i] + m_str1 + ")";
                m_str.push(str);

                //计算出结果；
                int str1 = m_num.top();
                m_num.pop();
                int str2 = m_num.top();
                m_num.pop();

                if (tokens[i] == "+")
                    m_num.push(str2 + str1);
                else if (tokens[i] == "-")
                    m_num.push(str2 - str1);
                else if (tokens[i] == "*")
                    m_num.push(str2 * str1);
                else if (tokens[i] == "/")
                    m_num.push(str2 / str1);
            }
            else
            {
                m_str.push(tokens[i]);
                m_num.push(stoi(tokens[i]));
            }
                
        }

        string str = m_str.top();
        m_str.pop();
        cout << "str: " << str << endl;

        int finalstr = m_num.top();
        m_num.pop();

        cout << "finalstr: " << finalstr << endl;

        if(m_num.size() > 1)
            cout << "worry string \n";
        else
            cout << "right string \n";
        
    }
};

int main(int argc, char const *argv[])
{
    Solution test;
    vector<string> tt = {"4", "13", "5", "/", "+"};
    test.evalRPN(tt);

    return 0;
}
