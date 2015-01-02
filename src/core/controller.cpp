/*
 * controller.cpp
 *
 *  Created on: Dec 23, 2014
 *      Author: mkolny
 */

#include "controller.h"
#include "IGui.h"
#include "logger.h"

#include "utils/gstreamerutils.h"

#include <boost/algorithm/string.hpp>

using namespace GstreamerStudio::Core;

Controller::Controller(const std::string& model_name, int argc, char** argv)
: GstreamerController(model_name, argc, argv)
{
}

void Controller::update_current_model (const Glib::RefPtr<Gst::Bin>& model)
{
  if (!model || !model->has_ancestor (master_model))
  {
    gui->current_model_changed(boost::join (Utils::GstreamerUtils::get_path (current_model), ":"));
    throw std::runtime_error("Model is not an descendant of a master model or model is empty");
  }

  current_model = model;
  auto path = Utils::GstreamerUtils::get_path (current_model);
  path.erase (path.begin ());
  gui->current_model_changed(boost::join (path, ":"));
}

void Controller::update_current_model (const std::string& model_path)
{
  std::vector<std::string> path;
  boost::algorithm::split (path, model_path, boost::is_any_of (":"));
  Glib::RefPtr<Gst::Object> model = Utils::GstreamerUtils::find_element(path, master_model);

  std::vector<std::string> vec_path = Utils::GstreamerUtils::get_path(current_model);
  vec_path.erase(vec_path.begin());
  std::string prev_path = boost::join (vec_path, ":");

  if (!model)
  {
    gui->current_model_changed (prev_path);
    throw std::runtime_error("Cannot find specified bin");
  }

  if (!model->is_bin())
  {
    gui->current_model_changed (prev_path);
    throw std::runtime_error("Type of model must be BIN");
  }

  try
  {
    update_current_model (Glib::RefPtr<Gst::Bin>::cast_static(model));
    gui->current_model_changed (model_path);
    Logger::get_instance ()->log ("changed model", LogLevel::DEBUG);
  }
  catch (const std::runtime_error& ex)
  {
    gui->current_model_changed (prev_path);
    throw ex;
  }
}
