#include <iostream>

using namespace std;


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL){}
};


#if 0
//递归方法
class Solution
{
public:
    bool checkValue(TreeNode *p, int sum)
    {
        if (p == NULL)
            return false;
        if (p->left == NULL && p->right == NULL)
            return p->val == sum;
        return checkValue(p->left, sum - p->val) || checkValue(p->right, sum - p->val);
    }

    bool hasPathSum(TreeNode *root, int sum)
    {
        return checkValue(root, sum);
    }
};
#endif


