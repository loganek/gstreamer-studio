/*
 * elementitem.h
 *
 *  Created on: Oct 27, 2014
 *      Author: loganek
 */

#ifndef ELEMENTITEM_H_
#define ELEMENTITEM_H_

#include "point.h"
#include "iselectableobserver.h"
#include "paditem.h"

#include <goocanvasmm-2.0/goocanvasmm.h>
#include <gstreamermm.h>

namespace GstreamerStudio {
namespace Clients {

class ElementItem : public Goocanvas::Group, public Core::IObservable<ISelectableObserver>
{
private:
  Glib::RefPtr<Gst::Element> model;
  bool grabbed = false;
  Point<double> grab_point;
  std::set<Glib::RefPtr<PadItem>> pads;

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

  void register_observer (ISelectableObserver* observer) override
  {
    IObservable<ISelectableObserver>::register_observer (observer);

    for (auto p : pads)
      p->register_observer (observer);
  }

  void unregister_observer (ISelectableObserver* observer) override
  {
    for (auto p : pads)
      p->unregister_observer (observer);

    IObservable<ISelectableObserver>::unregister_observer (observer);
  }

};

}
}



#endif /* ELEMENTITEM_H_ */
