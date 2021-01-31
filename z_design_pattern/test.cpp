#include "z_observer.h"
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

int main()
{
    printf("\n-------------testObserver----------------\n");
    testObserver();


    return 0;
}