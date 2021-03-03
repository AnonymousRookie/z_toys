#include "z_singleton.h"

NAMESPACE_BEGIN(z)

Singleton_Lazy* Singleton_Lazy::instance_ = nullptr;

Singleton_Lazy* Singleton_Lazy::instance()
{
    if (!instance_) {
        instance_ = new Singleton_Lazy();
    }
    return instance_;
}



Singleton_Hungry* Singleton_Hungry::instance_ = new Singleton_Hungry();

Singleton_Hungry* Singleton_Hungry::instance()
{
    return instance_;
}



Singleton_Lazy_ThreadSafe* Singleton_Lazy_ThreadSafe::instance_ = nullptr;

Singleton_Lazy_ThreadSafe::Singleton_Lazy_ThreadSafe() 
{
    printf("Singleton_Lazy_ThreadSafe()\n");
}

Singleton_Lazy_ThreadSafe* Singleton_Lazy_ThreadSafe::instance()
{
    // double check 
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_ = new Singleton_Lazy_ThreadSafe();
        }
    }
    return instance_;
}

NAMESPACE_END(z)
