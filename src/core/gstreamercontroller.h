/*
 * gstreamercontroller.h
 *
 *  Created on: Dec 23, 2014
 *      Author: mkolny
 */

#ifndef GSTREAMERCONTROLLER_H_
#define GSTREAMERCONTROLLER_H_

#include "IModelObserver.h"

#include <gstreamermm.h>

#include <set>

namespace GstreamerStudio {
namespace Core {

class GstreamerController
{
private:
  Glib::RefPtr<Gst::Pipeline> master_model; // todo should be const?
  Glib::RefPtr<Gst::Bin> current_model;
  std::vector<Glib::RefPtr<Gst::Pad>> sometimes_pads;
  std::set<IModelObserver*> observers;

  bool bus_method(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message);

  template<typename ...Args>
  void notify_observers(void (IModelObserver::* fun)(Args...), Args... args)
  {
    for (auto observer: observers)
      (observer->*fun)(args...);
  }

public:
  GstreamerController(const std::string& model_name, int argc = -1, char** argv = nullptr);
  virtual ~GstreamerController(){}
  Glib::RefPtr<Gst::Pipeline> get_master_model() const;
  Glib::RefPtr<Gst::Bin> get_current_model() const;
  void update_current_model(const Glib::RefPtr<Gst::Bin>& model);
  void export_bin_to_file(const std::string& filename, int graph_details, bool current_model);
  void register_model_observer(IModelObserver* observer);
  void unregister_model_observer(IModelObserver* observer);
};

}
}

#endif /* GSTREAMERCONTROLLER_H_ */
