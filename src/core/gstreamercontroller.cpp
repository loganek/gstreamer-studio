/*
 * gstreamercontroller.cpp
 *
 *  Created on: Dec 23, 2014
 *      Author: mkolny
 */

#include "gstreamercontroller.h"

using Glib::RefPtr;
using namespace Gst;
using namespace GstreamerStudio::Core;

GstreamerController::GstreamerController(const std::string& model_name, int argc, char** argv)
{
  if (argc == -1 || argv == nullptr)
    Gst::init();
  else
    Gst::init(argc, argv);

  current_model = master_model = Pipeline::create(model_name);
  master_model->get_bus()->add_watch(sigc::mem_fun(this, &GstreamerController::bus_method));
}

bool GstreamerController::bus_method(const RefPtr<Bus>& bus, const RefPtr<Message>& message)
{
  switch (message->get_message_type())
  {
  default:
    break;
  }

  return true;
}

void GstreamerController::update_current_model(const RefPtr<Bin>& model)
{
  RefPtr<Object> parent = model->get_parent();

  while (parent && parent != master_model)
  {
    parent = parent->get_parent();
  }

  if (!parent && model != master_model)
    throw std::runtime_error("Model is not an descendant of a master model");

  current_model = model;
}

Glib::RefPtr<Gst::Pipeline> GstreamerController::get_master_model() const
{
  return master_model;
}

Glib::RefPtr<Gst::Bin> GstreamerController::get_current_model() const
{
  return current_model;
}

void GstreamerController::export_bin_to_file(const std::string& filename, int graph_details, bool is_current_model)
{
  gst_debug_bin_to_dot_file(is_current_model ? current_model->gobj() : GST_BIN(master_model->gobj()),
    (GstDebugGraphDetails)graph_details, filename.c_str());
}

void GstreamerController::register_model_observer(IModelObserver* observer)
{
  if (!observers.insert(observer).second)
    throw std::runtime_error("Cannot register observer");
}

void GstreamerController::unregister_model_observer(IModelObserver* observer)
{
  if (!observers.erase(observer))
    throw std::runtime_error("Cannot unregister observer");
}
