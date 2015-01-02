/*
 * IObservable.h
 *
 *  Created on: Jan 2, 2015
 *      Author: loganek
 */

#ifndef IOBSERVABLE_H_
#define IOBSERVABLE_H_

#include <set>
#include <functional>
#include <memory>
#include <type_traits>

namespace GstreamerStudio {
namespace Core {

template<class OBSERVER>
class IObservable
{
protected:
  std::set<OBSERVER*> observers;

  template<typename ...T>
  void notify (typename std::common_type<std::function<void (OBSERVER*, IObservable<OBSERVER>*, T... value)>>::type fnc, T... values)
  {
    for (auto o : observers)
      fnc (o, this, values...);
  }

public:
  virtual ~IObservable () {}

  virtual void register_observer (OBSERVER* observer)
  {
    if (!observers.insert(observer).second)
      throw std::runtime_error("Cannot register observer");
  }

  virtual void unregister_observer (OBSERVER* observer)
  {
    if (!observers.erase (observer))
      throw std::runtime_error("Cannot unregister observer");
  }
};

}
}

#endif /* IOBSERVABLE_H_ */
