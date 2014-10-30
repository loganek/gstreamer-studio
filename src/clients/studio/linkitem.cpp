/*
 * linkitem.cpp
 *
 *  Created on: Oct 29, 2014
 *      Author: loganek
 */

#include "linkitem.h"
#include "paditem.h"

using namespace Goocanvas;
using namespace GstreamerStudio::Clients;
using Glib::RefPtr;

struct LinkItem::PadsModel
{
  Glib::RefPtr<PadItem> sink;
  Glib::RefPtr<PadItem> src;
};

RefPtr<LinkItem> LinkItem::create (const Point<double>& begin, const Point<double>& end,
  const RefPtr<Goocanvas::Item>& parent)
{
  RefPtr<LinkItem> item (new LinkItem (begin, end));
  parent->get_parent()->add_child (item);
  return item;
}

LinkItem::LinkItem (const Point<double>& begin, const Point<double>& end)
: Polyline (begin.x, begin.y, end.x, end.y),
  pads (std::make_shared<PadsModel> ())
{
  property_end_arrow () = true;
}
