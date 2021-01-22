/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
#include <iostream>
#include <queue>

using namespace std;

class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution
{
public:
    Node *connect(Node *root)
    {
        if (root == NULL)
            return NULL;

        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            Node *last = NULL;
            for (int i = 0; i < size; i++)
            {
                Node *tmp = q.front();
                q.pop();

                if (tmp->left)
                    q.push(tmp->left);

                if (tmp->right)
                    q.push(tmp->right);

                if (i != 0)
                    last->next = tmp;
                else
                    last = tmp;
            }
        }
        return root;
    }
};

class Solution
{
public:
    Node *connect(Node *root)
    {
        if (!root)
        {
            return nullptr;
        }
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            int n = q.size();
            Node *last = nullptr;
            for (int i = 1; i <= n; ++i)
            {
                Node *f = q.front();
                q.pop();
                if (f->left)
                {
                    q.push(f->left);
                }
                if (f->right)
                {
                    q.push(f->right);
                }
                if (i != 1)
                {
                    last->next = f;
                }
                last = f;
            }
        }
        return root;
    }
};



class Solution
{
public:
    Node *connect(Node *root)
    {
        if (root == NULL)
            return NULL;
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int size = q.size();
            Node *last = NULL;
            for (int i = 1; i <= size; ++i)
            {
                Node *tmp = q.front();
                q.pop();
                if (tmp->left)
                    q.push(tmp->left);
                if (tmp->right)
                    q.push(tmp->right);
                if (i != 1)
                    last->next = tmp;
                last = tmp;
            }
        }
        return root;
    }
};