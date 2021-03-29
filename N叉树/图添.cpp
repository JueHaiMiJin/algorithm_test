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
#include <string>

using namespace std;

class Codec
{
public:
    void digui(Node *root, string &str);
    {
        int len = root->children.size();
        if(len == 0) return 0;
        str += "[";
        char tmp_val[2] = {0};
        snprintf(tmp_val;, 2, "%d", root->val); 
        str += tmp_val;
        for(int i = 0; i < len; i++)
        {
            digui(root->children[i], str);
        }
        str += "]";
    }
    // Encodes a tree to a single string.
    string serialize(Node *root)
    {
        string str;
        digui(root, str);
        cout << "str: " << str << endl;
        return str;
    }

    // Decodes your encoded data to tree.
    Node *deserialize(string data)
    {
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));