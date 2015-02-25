#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <vector>

class Observable {
  /**
   * I elected to make these methods public and final (available in C++11)
   * to prevent classes implementing Observable to change the methods, while
   * allowing them to be called in the first place. Let me know if you think
   * we should remove the "final" (e.g., if you can think of a useful way to
   * override these methods.)    --Matthew
   **/
  public:
    Observer* AddObserver(const Observer *new_observer) final;
    Observer* RemoveObserver(const Observer *old_observer) final;
    void NotifyObservers() final;
  private:
    std::vector<Observer*> observer_list;
};

class Observer {
  public:
    virtual void Update() = 0;
};

#endif
