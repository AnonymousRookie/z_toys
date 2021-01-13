#include <iostream>
#include "z_vector.h"
#include "z_list.h"

void testVector()
{
    z::Vector<int> v1;
    for (int i = 0; i < 10; ++i) {
        v1.insert(i);
    }
    assert(v1.size() == 10);

    v1[0] = 123;
    for (int i = 0; i < v1.size(); ++i) {
        printf("%d ", v1[i]);
    }
    printf("\n");

    while (!v1.empty()) {
        v1.remove(0);
    }
    assert(v1.size() == 0);
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

int main()
{
    printf("\n-----------------------------\n");
    testVector();

    printf("\n-----------------------------\n");
    testList();

    return 0;
}
