#ifndef Z_DESIGN_PATTERN_OBSERVER_H
#define Z_DESIGN_PATTERN_OBSERVER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "defines.h"

NAMESPACE_BEGIN(z)

class Subject;

class Observer
{
public:
    Observer(const std::string& name) : name_(name) {
        printf("%s Observer()\n", name_.c_str());
    }
    ~Observer();

    void observe(Subject* s);

    void update() {
        printf("%s update...\n", name_.c_str());
    }

private:
    std::string name_;
    Subject* subject_;
};

class Subject
{
public:
    Subject() {
        printf("Subject()\n");
    }
    ~Subject() {
        printf("~Subject()\n");
    }

    void addObserver(Observer* o) {
        observers_.push_back(o);
    }

    void delObserver(Observer* o) {
        auto it = std::find(observers_.begin(), observers_.end(), o);
        if (it != observers_.end()) {
            it = observers_.erase(it);
        }
    }

    void notifyObservers() {
        for (Observer* o : observers_) {
            o->update();
        }
    }

private:
    std::vector<Observer*> observers_;
};

NAMESPACE_END(z)

#endif  // Z_DESIGN_PATTERN_OBSERVER_H