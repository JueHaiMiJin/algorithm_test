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

class Solution
{
public:
    int digui(Node *root)
    {
        if (root == NULL)
            return 0;
        int max = 0, tmp = 0;
        for (int i = 0; i < root->children.size(); i++)
        {
            tmp = digui(root->children[i]);
            max = (max > tmp) ? max : tmp;
        }
        return 1 + max;
    }

    int maxDepth(Node *root)
    {
        if (root == NULL)
            return 0;
        int max = digui(root);
        return max;
    }
};