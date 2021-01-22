/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// #include <iostream>

// struct TreeNode
// {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
// };
#include "pre.h"

#if 0
//递归
class Solution
{
public:
    TreeNode *test(vector<int> &inorder, vector<int> &postorder, int post_end, int in_start, int in_end)
    {
        if (in_end < in_start)
            return NULL;

        int curval = postorder[post_end];
        TreeNode *current = new TreeNode(curval);

        int index = 0;
        for (int i = 0; i < inorder.size(); i++)
        {
            if (curval == inorder[i])
                index = i;
        }

        TreeNode *left = test(inorder, postorder, post_end - (in_end - index) - 1, in_start, index - 1);
        TreeNode *right = test(inorder, postorder, post_end - 1, index + 1, in_end);

        current->left = left;
        current->right = right;
        return current;
    }
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        return test(inorder, postorder, postorder.size() - 1, 0, inorder.size() - 1);
    }
};
#endif


//更加高效
class Solution
{
    int post_idx;
    unordered_map<int, int> idx_map;

public:
    TreeNode *helper(int in_left, int in_right, vector<int> &inorder, vector<int> &postorder)
    {
        // 如果这里没有节点构造二叉树了，就结束
        if (in_left > in_right)
        {
            return nullptr;
        }

        // 选择 post_idx 位置的元素作为当前子树根节点
        int root_val = postorder[post_idx];
        TreeNode *root = new TreeNode(root_val);

        // 根据 root 所在位置分成左右两棵子树
        int index = idx_map[root_val];

        // 下标减一
        post_idx--;
        // 构造右子树
        root->right = helper(index + 1, in_right, inorder, postorder);
        // 构造左子树
        root->left = helper(in_left, index - 1, inorder, postorder);
        return root;
    }
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        // 从后序遍历的最后一个元素开始
        post_idx = (int)postorder.size() - 1;

        // 建立（元素，下标）键值对的哈希表
        int idx = 0;
        for (auto &val : inorder)
        {
            idx_map[val] = idx++;
        }
        return helper(0, (int)inorder.size() - 1, inorder, postorder);
    }
};