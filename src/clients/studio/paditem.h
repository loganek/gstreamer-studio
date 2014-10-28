/*
 * paditem.h
 *
 *  Created on: Oct 27, 2014
 *      Author: loganek
 */

#ifndef PADITEM_H_
#define PADITEM_H_

#include <goocanvasmm-2.0/goocanvasmm.h>
#include <gstreamermm.h>

namespace GstreamerStudio {
namespace Clients {

class PadItem : public Goocanvas::Group
{
private:
  Glib::RefPtr<Gst::Pad> model;

  void init ();
protected:
  explicit PadItem (const Glib::RefPtr<Gst::Pad>& model);

public:
  static Glib::RefPtr<PadItem> create (const Glib::RefPtr<Gst::Pad>& model, const Glib::RefPtr<Goocanvas::Item>& parent);

  // we need it, because property_{width|height} not working in all cases...
  double get_height () const;
  double get_width () const;

  bool is_sink () const;
};

}
}

#endif /* PADITEM_H_ */
