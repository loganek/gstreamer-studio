/*
 * plugininfowindow.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: loganek
 */

#include "plugininfowindow.h"

#include "core/plugininfo.h"

#include "gettext.h"

using namespace GstreamerStudio::Clients;
using namespace Gtk;

PluginInfoWindow::PluginInfoWindow (const std::string& plugin_name)
{
  builder = Builder::create_from_file ("src/clients/studio/ui/plugininfo.glade");

  builder->get_widget<Gtk::Window> ("pluginInfoWindow", window);

  Glib::RefPtr<ListStore> model = ListStore::create (model_columns);
  TreeView *tree = get_widget<TreeView> ("pluginTreeView");

  tree->append_column(_("Key"), model_columns.key);
  tree->append_column(_("Value"), model_columns.value);
  tree->set_model (model);

  for (auto item : GstreamerStudio::Core::PluginInfo ().get_plugin_info (plugin_name))
  {
    TreeModel::Row row = *(model->append ());
    row[model_columns.key] = item.first;
    row[model_columns.value] = item.second;
  }
}

PluginInfoWindow::~PluginInfoWindow ()
{
}

void PluginInfoWindow::show_window ()
{
  window->show_now ();
}

