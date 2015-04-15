#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <vector>

class Observer;

class Observable {
  public:
    Observer* AddObserver(Observer *new_observer);
    Observer* RemoveObserver(Observer *old_observer);
    void NotifyObservers();

  private:
    std::vector<Observer*> observer_list;
};

class Observer {
  public:
    virtual void Update() = 0;
};

#endif
