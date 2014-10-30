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
      ElementItem::get_from_child (item)->translate (motion->x - grab_point.x, motion->y - grab_point.y);
    return false;
  });

  signal_button_press_event ().connect ([this] (const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* evt) {
    auto cur = Gdk::Cursor::create (Gdk::FLEUR);
    grabbed = true;
    grab_point.update (evt->x, evt->y);
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
  item->redraw ();

  return item;
}

void ElementItem::init()
{
  title = Text::create(model->get_name(), 0, 0, 100, ANCHOR_CENTER);
  add_child (title);

  // cast is necessary, because of bug: https://bugzilla.gnome.org/show_bug.cgi?id=721627
  auto title_bounds = RefPtr<Item>::cast_static(title)->get_bounds();

  bounding_rectangle = Rect::create(title_bounds.get_x1 (), title_bounds.get_y1 (), 0, 0);
  bounding_rectangle->property_fill_color ().set_value ("aliceblue");
  add_child (bounding_rectangle);
  bounding_rectangle->lower ();

  auto sink_iterator = model->iterate_sink_pads ();

  double title_width = title_bounds.get_x2 () - title_bounds.get_x1 ();
  double lh = title_bounds.get_y2 () - title_bounds.get_y1 ();;
  double rh = lh;
  double lw = 0;
  while (sink_iterator.next ())
  {
    RefPtr<ElementItem> e (this); e->reference ();
    auto pad_item = PadItem::create (*sink_iterator, e);
    pad_item->translate (0, lh);
    lh += pad_item->get_height ();
    lw = std::max (pad_item->get_width (), lw);
  }

  auto src_iterator = model->iterate_src_pads ();

  double rw = 0;
  while (src_iterator.next ())
  {
    RefPtr<ElementItem> e (this); e->reference ();
    auto pad_item = PadItem::create (*src_iterator, e);
    pad_item->translate (0, rh);
    rh += pad_item->get_height ();
    rw = std::max (pad_item->get_width (), rw);
  }

  bounding_rectangle->property_height () = std::max (lh, rh);
  bounding_rectangle->property_width () = std::max (lw+rw, title_width);

  int mm =get_n_children();
  for (int i = 0; i < mm; i++)
  {
    if (auto a = RefPtr<PadItem>::cast_dynamic(get_child(i)))
    {
      if (a->is_sink ())
        continue;
      double mw = get_width ();
      a->translate (mw, 0);
    }
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

void ElementItem::redraw ()
{
  clear ();
  init ();
}

void ElementItem::clear ()
{
  while (get_n_children ())
    remove_child (0);
}

double ElementItem::get_height () const
{
  Bounds bounds = get_bounds();

  return bounds.get_y2 () - bounds.get_y1 ();
}

double ElementItem::get_width () const
{
  Bounds bounds = get_bounds();

  return bounds.get_x2 () - bounds.get_x1 ();
}
