/*
 * IModelObserver.h
 *
 *  Created on: Dec 23, 2014
 *      Author: mkolny
 */

#ifndef IMODELOBSERVER_H_
#define IMODELOBSERVER_H_

#include <gstreamermm.h>

namespace GstreamerStudio {
namespace Core {

class IModelObserver
{
public:
  virtual ~IModelObserver(){}
  virtual void pad_added(const Glib::RefPtr<Gst::Pad>& pad) {}
  virtual void pad_removed(const Glib::RefPtr<Gst::Pad>& pad) {}
  virtual void pad_linked(const Glib::RefPtr<Gst::Pad>& proxy_pad) {}
  virtual void pad_unlinked(const Glib::RefPtr<Gst::Pad>& proxy_pad) {}
  virtual void element_added(const Glib::RefPtr<Gst::Element>& element) {}
  virtual void element_removed(const Glib::RefPtr<Gst::Element>& element, const Glib::RefPtr<Gst::Bin>& bin) {}
  virtual void state_changed(const Glib::RefPtr<Gst::Element>& element, Gst::State state) {}
  virtual void property_changed(const Glib::RefPtr<Gst::Element>& element, const std::string& name) {}
};

}
}

#endif /* IMODELOBSERVER_H_ */
