#ifndef _PRE_H
#define _PRE_H

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifdef __cplusplus

extern "C"
{
    #include <stdio.h>
    #include <string.h>
};

#endif


using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#endif