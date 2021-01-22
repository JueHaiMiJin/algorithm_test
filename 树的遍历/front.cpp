// 方法一：递归
// 思路与算法

// 首先我们需要了解什么是二叉树的前序遍历：按照访问根节点——左子树——右子树的方式遍历这棵树，
// 而在访问左子树或者右子树的时候，我们按照同样的方式遍历，直到遍历完整棵树。
// 因此整个遍历过程天然具有递归的性质，我们可以直接用递归函数来模拟这一过程。

// 定义 preorder(root) 表示当前遍历到 root 节点的答案。
// 按照定义，我们只要首先将 root 节点的值加入答案，然后递归调用 preorder(root.left) 来遍历 root 节点的左子树，
// 最后递归调用 preorder(root.right) 来遍历 root 节点的右子树即可，递归终止的条件为碰到空节点。

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(): val(0), left(NULL), right(NULL){};
    TreeNode(int x): val(x), left(NULL), right(NULL){};
    TreeNode(int x, TreeNode *left, TreeNode *right):val(x), left(left),right(right){}; 
};

//前序遍历：根->左->右
class Solution
{
public:
    void bianli(TreeNode *root, vector<int> &ret)
    {
        if(root == NULL)
            return;
        else
        {
            ret.push_back(root->val);
            bianli(root->left, ret);
            bianli(root->right, ret);
        }
        
    }
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> m_ret;
        bianli(root, m_ret);
        return m_ret;
    }
};

//中序遍历： 左->根->右
class Solution
{
public:
    void bianli(TreeNode *root, vector<int> &ret)
    {
        if (root == NULL)
            return;
        else
        {
            bianli(root->left, ret);
            ret.push_back(root->val);
            bianli(root->right, ret);
        }
    }
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> m_ret;
        bianli(root, m_ret);
        return m_ret;
    }
};

//后序遍历： 左->右->根
class Solution
{
public:
    void bianli(TreeNode *root, vector<int> &ret)
    {
        if (root == NULL)
            return;
        else
        {
            bianli(root->left, ret);
            bianli(root->right, ret);
            ret.push_back(root->val);
        }
    }
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> m_ret;
        bianli(root, m_ret);
        return m_ret;
    }
};

// 方法二：迭代
// 思路与算法

// 我们也可以用迭代的方式实现方法一的递归函数，两种方式是等价的，区别在于递归的时候隐式地维护了一个栈，
// 而我们在迭代的时候需要显式地将这个栈模拟出来，其余的实现与细节都相同，具体可以参考下面的代码。

//前序遍历：根->左->右
class Solution
{
public:
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> m_ret;
        if(root == NULL)
            return m_ret;

        stack<TreeNode *> m_stack;
        m_stack.push(root);

        TreeNode* node = root;
        while (!m_stack.empty() && node != NULL)
        {
            while (node != NULL)
            {
                m_ret.push_back(node->val);
                m_stack.emplace(node);
                node = node->left;
            }

            node = m_stack.top();
            m_stack.pop();
            node = node->right;   
        }
        
    }
};

//中序遍历：左->根->右
class Solution
{
public:
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> m_ret;
        if (root == NULL)
            return m_ret;

        stack<TreeNode *> m_stack;
        m_stack.push(root);

        TreeNode *node = root;
        while (!m_stack.empty() && node != NULL)
        {
            while (node != NULL)
            {
                m_stack.emplace(node);
                node = node->left;
            }

            node = m_stack.top();
            m_ret.push_back(node->val);
            m_stack.pop();
            node = node->right;
        }
    }
};

//后序遍历：左->右->根
class Solution
{
public:
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> m_ret;
        if (root == NULL)
            return m_ret;

        stack<TreeNode *> m_stack;
        m_stack.push(root);

        TreeNode *node = root;
        while (!m_stack.empty() && node != NULL)
        {
            while (node != NULL)
            {
                m_stack.emplace(node);
                node = node->left;
            }

            node = m_stack.top();
            m_ret.push_back(node->val);
            m_stack.pop();
            node = node->right;
        }
    }
};


//广度搜索
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
public:
    //广度优先
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        queue<TreeNode *> q;
        vector<vector<int>> ret;
        if (root == NULL)
            return ret;

        q.push(root);

        while (!q.empty())
        {
            int size = q.size();
            vector<int> tmp;
            for (int i = 0; i < size; i++)
            {
                TreeNode *tmp_node = q.front();
                q.pop();

                tmp.push_back(tmp_node->val);

                if (tmp_node->left != NULL)
                    q.push(tmp_node->left);
                if (tmp_node->right != NULL)
                    q.push(tmp_node->right);
            }
            ret.push_back(tmp);
        }
        return ret;
    }
};

//                   1
//            2               3
//        4       5       6       7

// 如果对每一个节点进行编号，你会用什么方式去遍历每个节点呢？

// 如果你按照 根节点->左孩子->右孩子 的方式遍历，即「先序遍历」，每次先遍历根节点，遍历结果为 1 2 4 5 3 6 7；

// 同理，如果你按照 左孩子->根节点->右孩子 的方式遍历，即「中序序遍历」，遍历结果为 4 2 5 1 6 3 7；

// 如果你按照 左孩子->右孩子->根节点 的方式遍历，即「后序序遍历」，遍历结果为 4 5 2 6 7 3 1；

// 最后，层次遍历就是按照每一层从左向右的方式进行遍历，遍历结果为 1 2 3 4 5 6 7。

