/*
 * paditem.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: loganek
 */

#include "paditem.h"
#include "linkitem.h"
#include "sigcpp_lambda_hack.h"
#include <goocanvas-2.0/goocanvas.h>

using namespace Goocanvas;
using namespace GstreamerStudio::Clients;
using namespace Gst;
using Glib::RefPtr;

Glib::Quark PadItem::parent_pad_obj ("parent_pad_obj");

PadItem::PadItem (const RefPtr<Pad>& model)
: Group (),
  model (model)
{
  signal_button_press_event ().connect ([this] (const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* evt) {
    linking = true;
    Point<double> begin (
      get_bounds ().get_x2 (),
      (get_bounds ().get_y2 () + get_bounds ().get_y1 ()) / 2),
      end (evt->x_root, evt->y_root);
    link = LinkItem::create (begin, end, this->get_parent());
    item->get_canvas()->pointer_grab(item, static_cast<Gdk::EventMask>(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_RELEASE_MASK),
      Gdk::Cursor::create(Gdk::HAND2), GDK_CURRENT_TIME);
    return true;
  });

  signal_motion_notify_event ().connect ([this] (const Glib::RefPtr<Goocanvas::Item>& item,GdkEventMotion* motion) {
    if (linking)
    {
      Points pts = link->property_points ().get_value ();
      pts.set_coordinate(1, motion->x_root,  motion->y_root);
      link->property_points () = pts;

      auto underpad = check_underpad (motion->x_root, motion->y_root);

      if (underpad && underpad != this)
        puts ("ok, I'll do something here in the future"); // todo checking whether can link or not

      return true;
    }
    return false;
  });

  signal_button_release_event ().connect ([this] (const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* evt) {
    auto underpad = check_underpad (evt->x_root, evt->y_root);

    if (underpad && underpad != this)
      if (get_pad_model()->can_link(underpad->get_pad_model()))
      {
        linking = false;
      }
    if (linking)
    {
      link->remove ();
      linking = false;
    }
    return false;
  });

  signal_enter_notify_event ().connect ([this](const Glib::RefPtr<Item>& item, GdkEventCrossing*){
    rect->property_fill_color ().set_value ("pink");
    return false;
  });

  signal_leave_notify_event ().connect ([this](const Glib::RefPtr<Item>&,GdkEventCrossing*){
    if (!linking)
      rect->property_fill_color ().set_value ("lightgreen");
    return false;
  });
}

PadItem* PadItem::check_underpad(double x, double y) const
{
  // TODO I don't know why, but ->get_item_at doesn't work sometimes.
  RefPtr<Item> underitem2 = Glib::wrap(goo_canvas_get_item_at(const_cast<GooCanvas*>(get_canvas()->gobj()),
    x, y, false), true);

  RefPtr<ItemSimple> underitem = underitem.cast_static(underitem2);
  return (underitem) ?
    reinterpret_cast<PadItem*>(underitem->get_data (parent_pad_obj)) :
    nullptr;
}

RefPtr<PadItem> PadItem::create (const RefPtr<Pad>& model, const RefPtr<Goocanvas::Item>& parent)
{
  RefPtr<PadItem> item (new PadItem (model));
  parent->add_child (item);
  item->init ();

  return item;
}

void PadItem::init ()
{
  auto t = Text::create (model->get_name (), 0, 0, 100, ANCHOR_CENTER);
  t->set_data(parent_pad_obj, this);
  add_child (t);
  auto bounds = RefPtr<Item>::cast_static (t)->get_bounds (); // todo bugzilla workaround
  rect = Rect::create (bounds.get_x1 (), bounds.get_y1 (),
		  bounds.get_x2 () - bounds.get_x1 (), bounds.get_y2 () - bounds.get_y1 ());
  rect->property_fill_color ().set_value ("lightgreen");

  rect->set_data(parent_pad_obj, this);
  add_child (rect);
  rect->lower ();
}

double PadItem::get_height () const
{
  Bounds bounds = get_bounds();

  return bounds.get_y2 () - bounds.get_y1 ();
}

double PadItem::get_width () const
{
  Bounds bounds = get_bounds();

  return bounds.get_x2 () - bounds.get_x1 ();
}

bool PadItem::is_sink () const
{
  return model->get_direction () == Gst::PAD_SINK;
}
