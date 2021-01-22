/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <iostream>
#include <queue>
#include <unordered_map>


using namespace std;


struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

//思路：
//将所有的子节点与父节点相对应在fa这个map中
//通过查看val的值将p的父节点的位置在vis中的值设置为true
//便利q的父节点信息，如果发现vis[p->val]的值是true，则说明这个也是q的父节点，直接返回这个节点
class Solution
{
public:
    unordered_map<int, TreeNode*> fa;
    unordered_map<int, bool> vis;
    void dfs(TreeNode* root)
    {
        if(root->left != NULL)
        {
            fa[root->left->val] = root;
            dfs(root->left);
        } 

        if(root->right != NULL)
        {
            fa[root->right->val] = root;
            dfs(root->right);
        }
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        fa[root->val] = NULL;
        dfs(root);

        while (p != NULL)
        {
            vis[p->val] = true;
            p = fa[p->val];
        }

        while (q != NULL)
        {
            if(vis[q->val]) return q;
            q = fa[q->val];
        }
        
        return NULL;
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */



//思路
//递归的方式
//当走到某一个节点的位置时，如果左边的子树返回一个消息说p、q中的一个在子树中并且右边的子树也返回说p、q中的某一个在子树中，
//即可说明当前的节点是公共父节点，当然还有一种情况，当前的节点的值就是p、q中的一个，而左子树或右子树返回说p、q中的某一个在子树中
//也可以说明当前节点是公共父节点
//返回判断：如果左子树或者右子树任意一个返回p、q存在或者当前节点的值是p、q的值那么就返回true，向父节点报告

class Solution
{
public:
    TreeNode *ans;
    bool dfs(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == NULL)
            return false;
        bool lret = dfs(root->left, p, q);
        bool rret = dfs(root->right, p, q);

        if ((lret && rret) || (root->val == p->val || root->val == q->val) && (lret || rret))
            ans = root;
        return (lret || rret) || (root->val == p->val || root->val == q->val);
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (dfs(root, p, q))
            return ans;
        else
            return NULL;
    }
};