#ifndef Z_DATA_STRUCT_Z_BINARY_BINARY_H
#define Z_DATA_STRUCT_Z_BINARY_BINARY_H

#include "defines.h"
#include "z_vector.h"
#include "z_stack.h"

NAMESPACE_BEGIN(z)

template <class T>
struct BTNode
{
    T val;
    BTNode<T>* parent;  // 父节点
    BTNode<T>* lchild;  // 左孩子
    BTNode<T>* rchild;  // 右孩子

    BTNode() : parent(nullptr), lchild(nullptr), rchild(nullptr) {}
    BTNode(const T& v) : val(v), parent(nullptr), lchild(nullptr), rchild(nullptr) {}
};

template <class T>
class BinaryTree
{
public:
    BinaryTree() : root_(nullptr) {}
    ~BinaryTree();

    bool empty() const { return !root_; }
    BTNode<T>* root() const { return root_; }
    BTNode<T>* insertAsRoot(const T& val);  // 插入根节点
    BTNode<T>* insertAsLeftChild(BTNode<T>* node, const T& val); 
    BTNode<T>* insertAsRightChild(BTNode<T>* node, const T& val); 

    void preorderRecursiveTraversal(BTNode<T>* node, z::Vector<T>& ret);  // 先序遍历(递归)
    void preorderIterativeTraversal(BTNode<T>* node, z::Vector<T>& ret);  // 先序遍历(迭代)

    void inorderRecursiveTraversal(BTNode<T>* node, z::Vector<T>& ret);   // 中序遍历(递归)
    void inorderIterativeTraversal(BTNode<T>* node, z::Vector<T>& ret);   // 中序遍历(迭代)

    void postorderRecursiveTraversal(BTNode<T>* node, z::Vector<T>& ret); // 后序遍历(递归)
    void postorderIterativeTraversal(BTNode<T>* node, z::Vector<T>& ret); // 后序遍历(迭代)

    void levelTraversal(BTNode<T>* node, z::Vector<T>& ret);  // 按层次遍历

private:
    BTNode<T>* root_;  // 根节点
};

template <class T>
BinaryTree<T>::~BinaryTree() 
{

}

template <class T>
BTNode<T>* BinaryTree<T>::insertAsRoot(const T& val)
{
    root_ = new BTNode<T>(val);
    return root_;
}

template <class T>
BTNode<T>* BinaryTree<T>::insertAsLeftChild(BTNode<T>* node, const T& val)
{
    BTNode<T>* lchild = new BTNode<T>(val);
    node->lchild = lchild;
    return lchild;
}

template <class T>
BTNode<T>* BinaryTree<T>::insertAsRightChild(BTNode<T>* node, const T& val)
{
    BTNode<T>* rchild = new BTNode<T>(val);
    node->rchild = rchild;
    return rchild;
}   

// 先序遍历(递归)
template <class T>
void BinaryTree<T>::preorderRecursiveTraversal(BTNode<T>* node, z::Vector<T>& ret)
{
    if (!node) {
        return;
    }
    ret.push_back(node->val);
    preorderRecursiveTraversal(node->lchild, ret);
    preorderRecursiveTraversal(node->rchild, ret);
}


// 先序遍历(迭代)
template <class T>
void BinaryTree<T>::preorderIterativeTraversal(BTNode<T>* node, z::Vector<T>& ret)
{
    z::Stack<BTNode<T>*> stk;
    while (node || !stk.empty()) {
        while (node) {
            ret.push_back(node->val);
            stk.push(node->rchild);
            node = node->lchild;
        }
        node = stk.top();
        stk.pop();
    }
}  

// 中序遍历(递归)
template <class T>
void BinaryTree<T>::inorderRecursiveTraversal(BTNode<T>* node, z::Vector<T>& ret)
{
    if (!node) {
        return;
    }
    preorderRecursiveTraversal(node->lchild, ret);
    ret.push_back(node->val);
    preorderRecursiveTraversal(node->rchild, ret);
}

// 中序遍历(迭代)
template <class T>
void BinaryTree<T>::inorderIterativeTraversal(BTNode<T>* node, z::Vector<T>& ret)
{
    z::Stack<BTNode<T>*> stk;
    while (node || !stk.empty()) {
        while (node) {
            stk.push(node);
            node = node->lchild;
        }
        node = stk.top();
        stk.pop();
        ret.push_back(node->val);
        node = node->rchild;
    }
}

// 后序遍历(递归)
template <class T>
void BinaryTree<T>::postorderRecursiveTraversal(BTNode<T>* node, z::Vector<T>& ret)
{
    if (!node) {
        return;
    }
    postorderRecursiveTraversal(node->lchild, ret);
    postorderRecursiveTraversal(node->rchild, ret);
    ret.push_back(node->val);
}


// 后序遍历(迭代)
template <class T>
void BinaryTree<T>::postorderIterativeTraversal(BTNode<T>* node, z::Vector<T>& ret)
{

}


// 按层次遍历
template <class T>
void BinaryTree<T>::levelTraversal(BTNode<T>* node, z::Vector<T>& ret)
{

}

NAMESPACE_END(z)

#endif  // Z_DATA_STRUCT_Z_BINARY_BINARY_H