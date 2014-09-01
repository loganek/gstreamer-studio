/*
 * buildablegtk.h
 *
 *  Created on: Sep 1, 2014
 *      Author: loganek
 */

#ifndef BUILDABLEGTK_H_
#define BUILDABLEGTK_H_

#include <gtkmm.h>

namespace GstreamerStudio {
namespace Clients {

class BuildableGtk
{
protected:
  Glib::RefPtr<Gtk::Builder> builder;

  template<typename T>
  T* get_widget (const Glib::ustring& name)
  {
    T* widget = nullptr;
    builder->get_widget<T> (name, widget);

    if (widget == nullptr)
    {
      throw std::runtime_error ("cannot get " + name + " widget");
    }

    return widget;
  }

 public:
  virtual ~BuildableGtk () {}
};

}
}

#endif /* BUILDABLEGTK_H_ */
