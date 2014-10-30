/*
 * linkitem.h
 *
 *  Created on: Oct 29, 2014
 *      Author: loganek
 */

#ifndef LINKITEM_H_
#define LINKITEM_H_

#include "point.h"

#include <goocanvasmm-2.0/goocanvasmm.h>

#include <memory>

namespace GstreamerStudio {
namespace Clients {

class LinkItem : public Goocanvas::Polyline
{
private:
  struct PadsModel;
  std::shared_ptr<PadsModel> pads;

public:
  LinkItem (const Point<double>& begin, const Point<double>& end);
  virtual ~LinkItem () {}

  static Glib::RefPtr<LinkItem> create (const Point<double>& begin, const Point<double>& end,
    const Glib::RefPtr<Goocanvas::Item>& parent);
};

}
}

#endif /* LINKITEM_H_ */
