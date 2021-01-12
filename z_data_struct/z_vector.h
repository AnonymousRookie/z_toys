#ifndef Z_DATA_STRUCT_Z_VECTOR_H
#define Z_DATA_STRUCT_Z_VECTOR_H

#include "defines.h"

NAMESPACE_BEGIN(z)

template <class T>
class Vector
{
public:
    Vector(uint32_t capacity = kDefaultCapacity, uint32_t size = 0, T elem = 0);
    ~Vector();

    uint32_t size() const {
        return size_;
    }

    bool empty() const {
        return !size_;
    }

    T& operator[](uint32_t index) const;
    void insert(const T& elem);
    void remove(uint32_t index);

private:
    void expand();  // 空间不足时扩容
    void shrink();  // 装填因子过小时压缩
    void insert(uint32_t index, const T& elem);
    void remove(uint32_t left, uint32_t right);  // 删除区间[left, right)

private:
    const static uint32_t kDefaultCapacity = 4;
    T* element_;
    uint32_t capacity_;
    uint32_t size_;
};

template <class T>
Vector<T>::Vector(uint32_t capacity/* = kDefaultCapacity*/, uint32_t size/* = 0*/, T elem/* = 0*/)
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
T& Vector<T>::operator[](uint32_t index) const
{
    return element_[index];
}

template <class T>
void Vector<T>::insert(const T& elem)
{
    insert(size_, elem);
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
void Vector<T>::insert(uint32_t index, const T& elem)
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
void Vector<T>::remove(uint32_t index)
{
    remove(index, index + 1);
}

template <class T>
void Vector<T>::remove(uint32_t left, uint32_t right)
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