#include <iostream>
#include "z_vector.h"
#include "z_list.h"
#include "z_stack.h"
#include "z_deque.h"
#include "z_queue.h"
#include "z_binary_tree.h"

void printVector(const z::Vector<int>& vec)
{
    for (int i = 0; i < vec.size(); ++i) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

void testVector()
{
    z::Vector<int> v1;
    for (int i = 0; i < 10; ++i) {
        v1.push_back(i);
    }
    assert(v1.size() == 10);

    v1[0] = 123;
    for (int i = 0; i < v1.size(); ++i) {
        printf("%d ", v1[i]);
    }
    printf("\n");

    while (!v1.empty()) {
        v1.pop_back();
    }
    assert(v1.size() == 0);

    for (int i = 0; i < 10; ++i) {
        v1.push_back(i);
    }
    printf("v1.front() = %d\n", v1.front());
    printf("v1.back() = %d\n", v1.back());

    v1.front() = 111;
    v1.back() = 222;
    printf("v1.front() = %d\n", v1.front());
    printf("v1.back() = %d\n", v1.back());
}

void testList()
{
    z::List<int> l1;
    assert(l1.size() == 0);

    for (int i = 0; i < 10; ++i) {
        l1.push_back(i);
    }
    assert(l1.size() == 10);
    for (int i = 0; i < l1.size(); ++i) {
        printf("%d ", l1[i]);
    }
    printf("\n");
    l1.clear();
    assert(l1.empty());

    for (int i = 0; i < 10; ++i) {
        l1.push_front(i);
    }
    for (int i = 0; i < l1.size(); ++i) {
        printf("%d ", l1[i]);
    }
    printf("\n");
    l1.pop_back();
    l1.pop_front();
    assert(l1.size() == 8);

    for (int i = 0; i < l1.size(); ++i) {
        printf("%d ", l1[i]);
    }
    printf("\n");
}

void testStack()
{
    z::Stack<int> s1;
    for (int i = 0; i < 10; ++i) {
        s1.push(i);
    }
    while (!s1.empty()) {
        printf("%d ", s1.top());
        s1.pop();
    }
    assert(s1.size() == 0);
}

void testDeque()
{
    z::Deque<int> dq1;
    dq1.push_back(1);
    dq1.push_back(2);
    dq1.push_front(3);
    dq1.push_front(4);

    assert(dq1.front() == 4);
    assert(dq1.back() == 2);

    dq1.pop_back();
    assert(dq1.front() == 4);
    assert(dq1.back() == 1);

    dq1.pop_front();
    assert(dq1.front() == 3);
    assert(dq1.back() == 1);
}

void testQueue()
{
    z::Queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);
    assert(q1.size() == 3);
    assert(q1.top() == 1);

    q1.pop();
    assert(q1.top() == 2);
}

void testBinaryTree()
{
    /*
         1
        / \
       2   3
        \
         4
    */

    z::BinaryTree<int> bt;
    z::BTNode<int>* root = bt.insertAsRoot(1);
    z::BTNode<int>* lchild1 = bt.insertAsLeftChild(root, 2);
    z::BTNode<int>* rchild1 = bt.insertAsRightChild(root, 3);
    z::BTNode<int>* rchild2 = bt.insertAsRightChild(lchild1, 4);

    z::Vector<int> vals;

    vals.clear();
    bt.preorderRecursiveTraversal(root, vals);
    printf("preorderRecursiveTraversal: ");
    printVector(vals);

    vals.clear();
    bt.preorderIterativeTraversal(root, vals);
    printf("preorderIterativeTraversal: ");
    printVector(vals);

    vals.clear();
    bt.inorderRecursiveTraversal(root, vals);
    printf("inorderRecursiveTraversal: ");
    printVector(vals);

    vals.clear();
    bt.inorderIterativeTraversal(root, vals);
    printf("inorderIterativeTraversal: ");
    printVector(vals);

    vals.clear();
    bt.postorderRecursiveTraversal(root, vals);
    printf("postorderRecursiveTraversal: ");
    printVector(vals);

    vals.clear();
    bt.postorderIterativeTraversal(root, vals);
    printf("postorderIterativeTraversal: ");
    printVector(vals);

    vals.clear();
    bt.levelTraversal(root, vals);
    printf("levelTraversal: ");
    printVector(vals);
}

int main()
{
    printf("\n-------------testVector----------------\n");
    testVector();

    printf("\n-------------testList----------------\n");
    testList();

    printf("\n-------------testStack----------------\n");
    testStack();

    printf("\n-------------testDeque----------------\n");
    testDeque();

    printf("\n-------------testQueue----------------\n");
    testQueue();

    printf("\n-------------testBinaryTree----------------\n");
    testBinaryTree();

    return 0;
}
