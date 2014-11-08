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
    RefPtr<PadItem> this_pad (this); this_pad->reference ();
    linking = true;
    Point<double> begin (
      get_bounds ().get_x2 (),
      (get_bounds ().get_y2 () + get_bounds ().get_y1 ()) / 2),
      end (evt->x_root, evt->y_root);
    link = LinkItem::create (begin, end, this->get_parent());
    return true;
  });

  signal_motion_notify_event ().connect ([this] (const Glib::RefPtr<Goocanvas::Item>& item,GdkEventMotion* motion) {
    if (linking)
    {
      Points pts = link->property_points ().get_value ();
      pts.set_coordinate(1, motion->x_root,  motion->y_root);
      link->property_points () = pts;

      RefPtr<Item> underitem2 = Glib::wrap(goo_canvas_get_item_at(item->get_canvas()->gobj(), // TODO I don't know why, but
        motion->x_root, motion->y_root, false), true);                                        // but ->get_item_at doesn't work sometimes.
      RefPtr<ItemSimple> underitem = underitem.cast_static(underitem2);
      if (underitem)
      {
        auto underpad = reinterpret_cast<PadItem*>(underitem->get_data (parent_pad_obj));
        if (underpad)
          puts ("yeah");
      }
    }
    return false;
  });

  signal_button_release_event ().connect ([this] (const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* evt) {
    linking = false;
    link->remove ();
    return false;
  });
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
  auto r = Rect::create (bounds.get_x1 (), bounds.get_y1 (),
		  bounds.get_x2 () - bounds.get_x1 (), bounds.get_y2 () - bounds.get_y1 ());
  r->property_fill_color ().set_value ("lightgreen");

  r->set_data(parent_pad_obj, this);
  add_child (r);
  r->lower ();
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