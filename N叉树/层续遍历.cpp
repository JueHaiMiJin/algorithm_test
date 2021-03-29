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

class solution{
    public:
        vector<vector<int>> Get(Node* root)
        {
            if (root == NULL)
                return {};
            queue<Node *> tmp_list;
            tmp_list.push(root);
            vector<vector<int>> ret;
            while (tmp_list.size())
            {
                int count = tmp_list.size();
                vector<int> tmp_vect;
                for (int i = 0; i < count; i++)
                {
                    Node *tmp_node = tmp_list.front();
                    tmp_list.pop();
                    tmp_vect.push_back(tmp_node->val);

                    for (int i = 0; i < tmp_node->children.size(); i++)
                        tmp_list.push(tmp_node->children[i]);
                }
                ret.push_back(tmp_vect);
            }
            return ret;
        }
}
