#ifndef Z_DATA_STRUCT_Z_DEQUE_H
#define Z_DATA_STRUCT_Z_DEQUE_H

#include "defines.h"
#include "z_list.h"

NAMESPACE_BEGIN(z)

template <class T, class Container = List<T>>
class Deque
{
public:
    bool empty() const {
        return container_.empty();
    }

    size_type size() const {
        return container_.size();
    }

    T& front() {
        return container_.first()->data_;
    }
    T& back() {
        return container_.last()->data_;
    }

    void push_back(const T& val) {
        container_.push_back(val);
    }
    void push_front(const T& val) {
        container_.push_front(val);
    }
    void pop_back() {
        container_.pop_back();
    }
    void pop_front() {
        container_.pop_front();
    }
    void clear() {
        container_.clear();
    }

private:
    Container container_;
};

NAMESPACE_END(z)

#endif  // Z_DATA_STRUCT_Z_DEQUE_H