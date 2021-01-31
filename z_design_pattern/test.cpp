#include "z_observer.h"
#include "defines.h"

using namespace z;

void testObserver()
{
    Subject* subject = new Subject;

    Observer* o1 = new Observer("o1", subject);
    subject->addObserver(o1);

    Observer* o2 = new Observer("o2", subject);
    subject->addObserver(o2);

    subject->notifyObservers();

    subject->clear();
    delete subject;
    subject = nullptr;
}

int main()
{
    printf("\n-------------testObserver----------------\n");
    testObserver();


    return 0;
}