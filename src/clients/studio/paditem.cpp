/*
 * paditem.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: loganek
 */

#include "paditem.h"

using namespace Goocanvas;
using namespace GstreamerStudio::Clients;
using namespace Gst;
using Glib::RefPtr;

PadItem::PadItem (const RefPtr<Pad>& model)
: Group (),
  model (model)
{
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
  add_child (t);
  auto bounds = RefPtr<Item>::cast_static (t)->get_bounds (); // todo bugzilla workaround
  auto r = Rect::create (bounds.get_x1 (), bounds.get_y1 (),
		  bounds.get_x2 () - bounds.get_x1 (), bounds.get_y2 () - bounds.get_y1 ());
  r->property_fill_color ().set_value ("lightgreen");
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
