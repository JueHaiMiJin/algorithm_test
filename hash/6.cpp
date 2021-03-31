// Given two strings s and t, determine if they are isomorphic.

// Two strings s and t are isomorphic if the characters in s can be replaced to get t.

// All occurrences of a character must be replaced with another character while preserving the order of characters.No two characters may map to the same character,
// but a character may map to itself.

class Solution
{
public:
    bool isIsomorphic(string s, string t)
    {
        for (int i = 0; i < s.size(); ++i)
            if (s.find(s[i]) != t.find(t[i]))
                return false;
        return true;
    }
};

class Solution
{
public:
    bool isIsomorphic(string s, string t)
    {
        unordered_map<char, char> s2t;
        unordered_map<char, char> t2s;
        int len = s.length();
        for (int i = 0; i < len; ++i)
        {
            char x = s[i], y = t[i];
            if ((s2t.count(x) && s2t[x] != y) || (t2s.count(y) && t2s[y] != x))
            {
                return false;
            }
            s2t[x] = y;
            t2s[y] = x;
        }
        return true;
    }
};
