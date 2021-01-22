#include <iostream>
#include <list>
#include <stdio.h>
using namespace std;

template <typename T>
struct RedBlackNode
{
    int color;
    T value;

    struct RedBlackNode *parent;
    struct RedBlackNode *rchild;
    struct RedBlackNode *lchild;
};

template <typename T>
class RedBlackTree
{
public:
    RedBlackTree(){};

    void InitList();
    RedBlackNode<T> *CreateNolde();
    void LeftRotation(RedBlackNode<T> *&t);
    void RightRotation(RedBlackNode<T> *&t);

private:
    list<RedBlackNode<T>> m_list;

};

template <typename T>
void RedBlackTree<T>::InitList()
{
    RedBlackNode<T> tmp;
    tmp.color = 0;      //read 0, balck 1
    tmp.value = 1;

    tmp.lchild = NULL;
    tmp.rchild = NULL;

    tmp.parent = NULL;

    m_list.push_back(tmp);
    
}

template <typename T>
RedBlackNode<T>* RedBlackTree<T>::CreateNolde()
{

}

template <typename T>
void RedBlackTree<T>::LeftRotation(RedBlackNode<T> *&t)
{
    RedBlackNode<T> *temp = t->rchild;
    t->rchild = temp->lchild;
    if (Parent(t) == NIL)
    {
        root = temp;
    }
    temp->lchild = t;
    Parent(t)->rchild = temp;
}

template <typename T>
void RedBlackTree<T>::RightRotation(RedBlackNode<T> *&t)
{
    RedBlackNode<T> *temp = t->lchild;
    t->lchild = temp->rchild;
    if (Parent(t) == NIL)
    {
        root = temp;
    }
    temp->rchild = t;
    Parent(t)->lchild = temp;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

