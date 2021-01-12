#include <iostream>
#include "z_vector.h"

int main()
{
    z::Vector<int> v1;
    for (int i = 0; i < 10; ++i) {
        v1.insert(i);
    }
    assert(v1.size() == 10);

    while (!v1.empty()) {
        v1.remove(0);
    }
    assert(v1.size() == 0);

    return 0;
}
