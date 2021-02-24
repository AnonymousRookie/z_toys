#ifndef Z_DESIGN_PATTERN_SINGLETON_H
#define Z_DESIGN_PATTERN_SINGLETON_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "defines.h"

NAMESPACE_BEGIN(z)

// 懒汉式
class Singleton_Lazy
{
private:
    Singleton_Lazy() {}

public:
    static Singleton_Lazy* instance();

private:
    static Singleton_Lazy* instance_;
};

// 饿汉式
class Singleton_Hungry
{
private:
    Singleton_Hungry() {}

public:
    static Singleton_Hungry* instance();

private:
    static Singleton_Hungry* instance_;
};


NAMESPACE_END(z)

#endif  // Z_DESIGN_PATTERN_SINGLETON_H