#include <thread>
#include "z_observer.h"
#include "z_singleton.h"
#include "defines.h"

using namespace z;

void testObserver()
{
    Subject* subject = new Subject;

    Observer* o1 = new Observer("o1");
    o1->observe(subject);

    Observer* o2 = new Observer("o2");
    o2->observe(subject);

    subject->notifyObservers();

    delete o1;
    delete o2;
    delete subject;
}

void testSingleton()
{
    Singleton_Lazy* instance1 = Singleton_Lazy::instance();
    Singleton_Lazy* instance2 = Singleton_Lazy::instance();
    assert(instance1 == instance2);

    Singleton_Hungry* instance3 = Singleton_Hungry::instance();
    Singleton_Hungry* instance4 = Singleton_Hungry::instance();
    assert(instance3 == instance4);


    std::thread t1([](){ Singleton_Lazy_ThreadSafe::instance(); });
    std::thread t2([](){ Singleton_Lazy_ThreadSafe::instance(); });
    std::thread t3([](){ Singleton_Lazy_ThreadSafe::instance(); });
    std::thread t4([](){ Singleton_Lazy_ThreadSafe::instance(); });
    std::thread t5([](){ Singleton_Lazy_ThreadSafe::instance(); });
    std::thread t6([](){ Singleton_Lazy_ThreadSafe::instance(); });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
}

int main()
{
    printf("\n-------------testObserver----------------\n");
    testObserver();

    printf("\n-------------testSingleton----------------\n");
    testSingleton();

    return 0;
}