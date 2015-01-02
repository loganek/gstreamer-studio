/*
 * controller.h
 *
 *  Created on: Dec 23, 2014
 *      Author: mkolny
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "gstreamercontroller.h"

#include <gstreamermm.h>

namespace GstreamerStudio {
namespace Core {

class IGui;

class Controller : public GstreamerController
{
private:
  IGui* gui = nullptr;
public:
  Controller(const std::string& model_name, int argc = -1, char** argv = nullptr);
  virtual ~Controller() {}

  void update_current_model(const std::string& model_path);
  void update_current_model(const Glib::RefPtr<Gst::Bin>& model);

  void call_command(const std::string& cmd_text);

  void set_gui(IGui* gui) { this->gui = gui; }
  void export_bin_to_file(const std::string& filename,
    int graph_details, bool is_master_model);

  Glib::RefPtr<Gst::Bin> get_current_model() const;

  void register_model_observer(IModelObserver* observer);
  void unregister_model_observer(IModelObserver* observer);
};


}
}

#endif /* CONTROLLER_H_ */
