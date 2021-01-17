#ifndef Z_DATA_STRUCT_Z_STACK_H
#define Z_DATA_STRUCT_Z_STACK_H

#include "defines.h"
#include "z_stack.h"

NAMESPACE_BEGIN(z)

template <class T, class Container = Vector<T>>
class Stack
{
public:
    bool empty() const {
        return container_.empty();
    }

    size_type size() const {
        return container_.size();
    }

    T& top() {
        return container_.back();
    }

    void push(const T& val) {
        container_.push_back(val);
    }

    void pop() {
        container_.pop_back();
    }

private:
    Container container_;
};

NAMESPACE_END(z)

#endif  // Z_DATA_STRUCT_Z_STACK_H