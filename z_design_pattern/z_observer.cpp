#include "z_observer.h"

NAMESPACE_BEGIN(z)

Observer::~Observer() {
    printf("%s ~Observer()\n", name_.c_str());
    subject_->delObserver(this);
}

void Observer::observe(Subject* s) 
{
    s->addObserver(this);
    subject_ = s;
}

NAMESPACE_END(z)