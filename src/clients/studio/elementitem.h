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

class ElementItem : public Goocanvas::Group
{
private:
  Glib::RefPtr<Gst::Element> model;
  bool grabbed = false;

  void init();
protected:
  explicit ElementItem (const Glib::RefPtr<Gst::Element>& model);

public:
  static Glib::RefPtr<ElementItem> create (const Glib::RefPtr<Gst::Element>& model, const Glib::RefPtr<Goocanvas::Item>& parent);

  static Glib::RefPtr<ElementItem> get_from_child (const Glib::RefPtr<Goocanvas::Item>& item);
};

}
}



#endif /* ELEMENTITEM_H_ */
