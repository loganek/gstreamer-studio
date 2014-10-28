/*
 * elementitem.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: loganek
 */

#include "elementitem.h"
#include "paditem.h"
#include "sigcpp_lambda_hack.h"

using namespace GstreamerStudio::Clients;
using namespace Goocanvas;
using namespace Gst;
using Glib::RefPtr;

ElementItem::ElementItem (const RefPtr<Element>& model)
: Group (),
  model (model)
{
  signal_motion_notify_event ().connect ([this] (const Glib::RefPtr<Goocanvas::Item>& item,GdkEventMotion* motion) {
    if (grabbed)
      ElementItem::get_from_child (item)->translate (motion->x, motion->y);
      return false;
  });

  signal_button_press_event ().connect ([this] (const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* evt) {
    auto cur = Gdk::Cursor::create (Gdk::FLEUR);
    grabbed = true;
    item->get_canvas ()->pointer_grab (item, (Gdk::EventMask)(GDK_POINTER_MOTION_MASK | GDK_BUTTON_RELEASE_MASK), cur, evt->time);
    return false;
  });

  signal_button_release_event ().connect ([this] (const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* evt) {
    item->get_canvas()->pointer_ungrab (item, evt->time);
    grabbed = false;
    return false;
  });
}

RefPtr<ElementItem> ElementItem::create (const RefPtr<Element>& model, const Glib::RefPtr<Goocanvas::Item>& parent)
{
  RefPtr<ElementItem> item (new ElementItem (model));
  parent->add_child (item);
  item->init ();
  return item;
}

void ElementItem::init()
{
  auto t = Text::create(model->get_name(), 20, 20, 100, ANCHOR_CENTER);
  add_child (t);

  // cast is necessary, because of bug: https://bugzilla.gnome.org/show_bug.cgi?id=721627
  auto bounds = RefPtr<Item>::cast_static(t)->get_bounds();
  auto r = Rect::create(bounds.get_x1 () - 10, bounds.get_y1 () - 10, bounds.get_x2 () - bounds.get_x1 () + 20, bounds.get_y2 () - bounds.get_y1 () + 120);
  r->property_fill_color().set_value("aliceblue");
  add_child (r);
  r->lower();

  auto sink_iterator = model->iterate_pads ();

  while (sink_iterator.next ())
  {
    RefPtr<ElementItem> e (this); e->reference ();
    PadItem::create (*sink_iterator, e);
  }
}


RefPtr<ElementItem> ElementItem::get_from_child (const RefPtr<Goocanvas::Item>& item)
{
  auto i = item;

  while (!RefPtr<ElementItem>::cast_dynamic(i) && i)
  {
    i = i->get_parent();
  }

  return RefPtr<ElementItem>::cast_dynamic (i);
}
