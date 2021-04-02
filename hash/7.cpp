// 假设Andy和Doris想在晚餐时选择一家餐厅，并且他们都有一个表示最喜爱餐厅的列表，每个餐厅的名字用字符串表示。

// 你需要帮助他们用最少的索引和找出他们共同喜爱的餐厅。 如果答案不止一个，则输出所有答案并且不考虑顺序。 你可以假设总是存在一个答案。
// leetcode 599

class Solution
{
    unordered_map<string, int> m_map;
    vector<pair<string, int>> m_ret;

public:
    vector<string> findRestaurant(vector<string> &list1, vector<string> &list2)
    {
        vector<string> ret;
        for (int i = 0; i < list1.size(); i++)
            m_map[list1[i]] = i;

        for (int i = 0; i < list2.size(); i++)
        {
            if (m_map.count(list2[i]) > 0)
                m_ret.push_back(make_pair(list2[i], m_map[list2[i]] + i));
        }

        std::sort(m_ret.begin(), m_ret.end(),
                  [](const pair<string, int> &a, const pair<string, int> &b) { return a.second < b.second; });

        if (m_ret.size() == 0)
        {
            return {};
        }
        else if (m_ret.size() == 1)
        {
            return {m_ret[0].first};
        }
        else
        {
            for (int i = 0; i < m_ret.size(); i++)
            {
                if ((i + 1) < m_ret.size() && m_ret[i].second != m_ret[i + 1].second)
                {
                    ret.push_back(m_ret[i].first);
                    break;
                }
                else
                {
                    ret.push_back(m_ret[i].first);
                }
            }
        }

        return ret;
    }
};


//高效版本
class Solution
{
public:
    vector<string> findRestaurant(vector<string> &list1, vector<string> &list2)
    {
        unordered_map<string, int> m_map;
        vector<string> ret;
        int m_min = INT_MAX;

        for (int i = 0; i < list1.size(); i++)
            m_map[list1[i]] = i;

        for (int i = 0; i < list2.size(); i++)
        {
            if (m_map.count(list2[i]) > 0)
            {
                int tmp = m_min;
                m_min = min(m_min, m_map[list2[i]] + i);
                if (tmp > m_min)
                {
                    ret.clear();
                    ret.push_back(list2[i]);
                }
                else if (tmp == m_min && m_min == (m_map[list2[i]] + i))
                {
                    ret.push_back(list2[i]);
                }
            }
        }
        return ret;
    }
};