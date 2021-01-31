#ifndef Z_DESIGN_PATTERN_OBSERVER_H
#define Z_DESIGN_PATTERN_OBSERVER_H

#include <iostream>
#include <vector>
#include <string>
#include "defines.h"

NAMESPACE_BEGIN(z)

class Subject;

class Observer
{
public:
    Observer(const std::string& name, Subject* subject) : name_(name), subject_(subject) {
        printf("%s Observer()\n", name_.c_str());
    }
    ~Observer() {
        printf("%s ~Observer()\n", name_.c_str());
    }

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

    }

    void notifyObservers() {
        for (Observer* o : observers_) {
            o->update();
        }
    }

    void clear() {
        for (Observer* o : observers_) {
            delete o;
            o = nullptr;
        }
    }

private:
    std::vector<Observer*> observers_;
};

NAMESPACE_END(z)

#endif  // Z_DESIGN_PATTERN_OBSERVER_H