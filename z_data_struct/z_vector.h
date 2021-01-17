#ifndef Z_DATA_STRUCT_Z_VECTOR_H
#define Z_DATA_STRUCT_Z_VECTOR_H

#include "defines.h"

NAMESPACE_BEGIN(z)

template <class T>
class Vector
{
public:
    Vector(size_type capacity = kDefaultCapacity, size_type size = 0, T elem = 0);
    ~Vector();

    size_type size() const {
        return size_;
    }

    bool empty() const {
        return !size_;
    }

    T& operator[](size_type index) const;
    void insert(const T& elem);
    void remove(size_type index);
    void push_back(const T& elem);
    void pop_back();
    
    T& front() {
        return element_[0];
    }
    T& back() {
        return element_[size_ - 1];
    }

private:
    void expand();  // 空间不足时扩容
    void shrink();  // 装填因子过小时压缩
    void insert(size_type index, const T& elem);
    void remove(size_type left, size_type right);  // 删除区间[left, right)

private:
    const static uint32_t kDefaultCapacity = 4;
    T* element_;
    size_type capacity_;
    size_type size_;
};

template <class T>
Vector<T>::Vector(size_type capacity/* = kDefaultCapacity*/, size_type size/* = 0*/, T elem/* = 0*/)
    : capacity_(capacity)
    , size_(size)
{
    if (capacity_ < size_) {
        capacity_ = size_;
    }

    if (capacity_ < kDefaultCapacity) {
        capacity_ = kDefaultCapacity;
    }

    element_ = new T[capacity_];
    for (int i = 0; i < size_; ++i)
    {
        element_[i] = elem;
    }
}

template <class T>
Vector<T>::~Vector()
{
    delete[] element_;
}

template <class T>
T& Vector<T>::operator[](size_type index) const
{
    return element_[index];
}

template <class T>
void Vector<T>::insert(const T& elem)
{
    insert(size_, elem);
}

template <class T>
void Vector<T>::push_back(const T& elem)
{
    insert(size_, elem);
}

template <class T>
void Vector<T>::pop_back()
{
    remove(size_ - 1);
}

template <class T>
void Vector<T>::expand()
{
    if (size_ < capacity_) {
        return;
    }

    if (capacity_ < kDefaultCapacity) {
        capacity_ = kDefaultCapacity;
    }

    printf("expand...\n");
    printf("old capacity_ = %d\n", capacity_);

    T* oldElem = element_;
    capacity_ <<= 1;  // 容量加倍
    element_ = new T[capacity_];
    for (int i = 0; i < size_; ++i) {
        element_[i] = oldElem[i];
    }
    delete[] oldElem;

    printf("new capacity_ = %d\n", capacity_);
}

template <class T>
void Vector<T>::shrink()
{
    if (size_ > (capacity_ >> 2)) {
        return;
    }
    if ((capacity_ >> 1) < kDefaultCapacity) {
        return;
    }

    printf("shrink...\n");
    printf("old capacity_ = %d\n", capacity_);

    capacity_ >>= 1;  // 容量减半
    T* oldElem = element_;
    element_ = new T[capacity_];
    for (int i = 0; i < size_; ++i) {
        element_[i] = oldElem[i];
    }
    delete[] oldElem;

    printf("new capacity_ = %d\n", capacity_);
}

template <class T>
void Vector<T>::insert(size_type index, const T& elem)
{
    if (index > size_) {
        return;
    }

    expand();

    for (int i = size_; i > index; --i) {
        element_[i] = element_[i-1];
    }
    element_[index] = elem;
    ++size_;
}

template <class T>
void Vector<T>::remove(size_type index)
{
    remove(index, index + 1);
}

template <class T>
void Vector<T>::remove(size_type left, size_type right)
{
    if (left >= right || right > size_) {
        return;
    }

    while (right < size_) {
        element_[left++] = element_[right++];
    }

    size_ -= (right - left);
    shrink();
}

NAMESPACE_END(z)

#endif  // Z_DATA_STRUCT_Z_VECTOR_H