#ifndef Z_DATA_STRUCT_Z_LIST_H
#define Z_DATA_STRUCT_Z_LIST_H

#include "defines.h"

NAMESPACE_BEGIN(z)

template <class T>
class ListNode
{
public:
    ListNode() {}
    ListNode(const T& data) : data_(data) {}

    T data_;
    ListNode<T>* pre_;
    ListNode<T>* next_;
};

template <class T>
class List
{
public:
    List();
    ~List();

    size_type size() const {
        return size_;
    }

    bool empty() const {
        return !size_;
    }

    // 首节点
    ListNode<T>* first() const {
        return headNode_->next_;
    }

    // 末节点
    ListNode<T>* last() const {
        return tailNode_->pre_;
    }

    T& operator[](size_type i) const;

    T remove(ListNode<T>* node);

    void push_front(const T& data);
    void pop_front();
    void push_back(const T& data);
    void pop_back();

    void clear();

private:
    size_type size_;
    ListNode<T>* headNode_;  // 头节点(哨兵节点, 紧邻于首节点之前)
    ListNode<T>* tailNode_;  // 尾节点(哨兵节点, 紧邻于末节点之后)
};


template <class T>
List<T>::List()
{
    headNode_ = new ListNode<T>();
    tailNode_ = new ListNode<T>();

    headNode_->pre_ = nullptr;
    headNode_->next_ = tailNode_;

    tailNode_->pre_ = headNode_;
    tailNode_->next_ = nullptr;

    size_ = 0;
}

template <class T>
List<T>::~List()
{
    clear();

    delete headNode_;
    delete tailNode_;
}

template <class T>
T& List<T>::operator[](size_type i) const
{
    assert(i >= 0 && i < size_);
    if (i > (size_ >> 1)) {
        // 从后往前查找
        ListNode<T>* node = last();
        size_type j = size_ - i - 1;
        while (j--) {
            node = node->pre_;
        }
        return node->data_;
    }
    else {
        // 从前往后查找
        ListNode<T>* node = first();
        while (i--) {
            node = node->next_;
        }
        return node->data_;
    }
}

template <class T>
T List<T>::remove(ListNode<T>* node)
{
    T data = node->data_;

    node->pre_->next_ = node->next_;
    node->next_->pre_ = node->pre_;

    delete node;
    --size_;
    return data;
}

template <class T>
void List<T>::push_front(const T& data)
{
    ListNode<T>* node = new ListNode<T>(data);

    ListNode<T>* temp = headNode_->next_;
    headNode_->next_ = node;
    node->pre_ = headNode_;

    temp->pre_ = node;
    node->next_ = temp;

    ++size_;
}

template <class T>
void List<T>::pop_front()
{
    remove(first());
}

template <class T>
void List<T>::push_back(const T& data)
{
    ListNode<T>* node = new ListNode<T>(data);

    ListNode<T>* temp = tailNode_->pre_;
    temp->next_ = node;
    node->pre_ = temp;

    node->next_ = tailNode_;
    tailNode_->pre_ = node;

    ++size_;
}

template <class T>
void List<T>::pop_back()
{
    remove(last());
}


template <class T>
void List<T>::clear()
{
    while (!empty()) {
        // 反复删除首节点
        remove(first());
    }
}

NAMESPACE_END(z)

#endif  // Z_DATA_STRUCT_Z_LIST_H