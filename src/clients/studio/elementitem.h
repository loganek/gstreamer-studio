/*
 * elementitem.h
 *
 *  Created on: Oct 27, 2014
 *      Author: loganek
 */

#ifndef ELEMENTITEM_H_
#define ELEMENTITEM_H_

#include <goocanvasmm-2.0/goocanvasmm.h>
#include <gstreamermm.h>

namespace GstreamerStudio {
namespace Clients {

// todo I'm almost sure, in goocanvas library is a similar class...
template<typename T>
struct Point
{
  T x;
  T y;

  void update (const T& x, const T& y)
  {
    this->x = x;
    this->y = y;
  }
};

class ElementItem : public Goocanvas::Group
{
private:
  Glib::RefPtr<Gst::Element> model;
  bool grabbed = false;
  Point<double> grab_point;

  Glib::RefPtr<Goocanvas::Rect> bounding_rectangle;
  Glib::RefPtr<Goocanvas::Text> title;

  void init ();
  void clear ();
  void redraw ();
protected:
  explicit ElementItem (const Glib::RefPtr<Gst::Element>& model);

public:
  static Glib::RefPtr<ElementItem> create (const Glib::RefPtr<Gst::Element>& model, const Glib::RefPtr<Goocanvas::Item>& parent);

  static Glib::RefPtr<ElementItem> get_from_child (const Glib::RefPtr<Goocanvas::Item>& item);

  // todo ough, copy&paste from PadItem class
  double get_height () const;
  double get_width () const;
};

}
}



#endif /* ELEMENTITEM_H_ */
