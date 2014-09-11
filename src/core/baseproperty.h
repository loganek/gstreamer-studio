/*
 * baseproperty.h
 *
 *  Created on: Sep 11, 2014
 *      Author: loganek
 */

#ifndef BASEPROPERTY_H_
#define BASEPROPERTY_H_

#include <glib-object.h>

#include <string>

namespace GstreamerStudio {
namespace Core {

class GstBaseProperty
{
public:
  virtual ~GstBaseProperty () {}
};

template<typename T>
class BaseProperty : public GstBaseProperty
{
protected:
  T value;
  T default_value;
  T min;
  T max;

public:
  T get_value () const
  {
    return value;
  }
  T get_default_value () const
  {
    return default_value;
  }
  T get_min () const
  {
    return min;
  }
  T get_max () const
  {
    return max;
  }

  BaseProperty (const T& default_value, const T& value)
  : value (value), default_value (default_value)
  {
  }

  BaseProperty (const T& default_value, const T& value, const T& min, const T& max);
};

class GstProperty
{
private:
  GstBaseProperty *property_base;
  GParamSpec *spec;

public:
  GstProperty (GParamSpec *param_spec);
  virtual ~GstProperty ();

  template<typename T>
  BaseProperty<T>* get_property ()
  {
    return dynamic_cast<BaseProperty<T>*> (property_base);
  }

  std::string get_name () const;
  std::string get_description () const;
  bool is_readable () const;
  bool is_writable () const;
  bool is_controllable () const;
  bool is_mutable_playing() const;
  bool is_mutable_paused () const;
  bool is_mutable_ready () const;
};

}
}

#endif /* BASEPROPERTY_H_ */
