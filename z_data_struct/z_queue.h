#ifndef Z_DATA_STRUCT_Z_QUEUE_H
#define Z_DATA_STRUCT_Z_QUEUE_H

#include "defines.h"
#include "z_deque.h"

NAMESPACE_BEGIN(z)

template <class T, class Container = Deque<T>>
class Queue
{
public:
    bool empty() const {
        return container_.empty();
    }

    size_type size() const {
        return container_.size();
    }

    T& top() {
        return container_.front();
    }

    void push(const T& val) {
        container_.push_back(val);
    }

    void pop() {
        container_.pop_front();
    }

private:
    Container container_;
};

NAMESPACE_END(z)

#endif  // Z_DATA_STRUCT_Z_QUEUE_H