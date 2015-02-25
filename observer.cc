#include <algorithm> // std::remove
#include <vector>

#include "observer.h"

Observer Observable::AddObserver(const Observer *new_observer) {
  for (auto &observer : observer_list) {
    if (observer == new_observer) {
      return observer;
    }
  }
  observer_list.push_back(new_observer);
  return new_observer;
}

Observable::RemoveObserver(const Observer *old_observer) {
  // This monster line basically says: get me the new end iterator (with
  // std::remove) and apply erase to the vector (removing the element).
  observer_list.erase(std::remove(observer_list.begin() observer_list.end(), old_observer), observer_list.end());
}

void Observable::NotifyObservers() {
  for (auto &observer : observer_list) {
    observer.Update();
  } 
}
