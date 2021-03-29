/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution
{
public:
    void digui(Node *root, vector<int> &ret)
    {
        ret.push_back(root->val);
        int len = root->children.size();
        if (len == 0)
            return;
        for (int i = 0; i < len; i++)
        {
            digui(root->children[i], ret);
        }
    }
    vector<int> preorder(Node *root)
    {
        if (root == NULL)
            return {};
        vector<int> ret;
        digui(root, ret);
        return ret;
    }
};