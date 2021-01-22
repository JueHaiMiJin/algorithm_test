/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include "pre.h"

class Codec
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        if (root == NULL)
            return "#_";
        string ret = std::to_string(root->val) + "_";
        ret += serialize(root->left);
        ret += serialize(root->right);
        return ret;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        std::stringstream ss(data);
        string item;
        queue<string> q;
        while (getline(ss, item, '_'))
        {
            q.push(item);
        }
        return help(q);
    }

    TreeNode *help(queue<string> &q)
    {
        string val = q.front();
        q.pop();
        if (val == "#")
            return NULL;
        TreeNode *head = new TreeNode(stoi(val));
        head->left = help(q);
        head->right = help(q);

        return head;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));