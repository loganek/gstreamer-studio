/*
 * factoryinfowindow.cpp
 *
 *  Created on: Sep 2, 2014
 *      Author: loganek
 */

#include "factoryinfowindow.h"
#include "plugininfowindow.h"

#include "core/plugininfo.h"

using namespace GstreamerStudio::Clients;
using namespace Gtk;

FactoryInfoWindow::FactoryInfoWindow (const std::string& factory_name)
{
  builder = Builder::create_from_file ("src/clients/studio/ui/plugininfo.glade");

  builder->get_widget<Gtk::Window> ("elementInfoWindow", window);

  Glib::RefPtr<ListStore> model = ListStore::create (model_columns);
  TreeView *tree = get_widget<TreeView> ("metadataTreeView");

  tree->append_column("Key", model_columns.key);
  tree->append_column("Value", model_columns.value);
  tree->set_model (model);

  GstreamerStudio::Core::PluginInfo plugin_info;

  for (auto item : plugin_info.get_factory_metadata (factory_name))
  {
    TreeModel::Row row = *(model->append ());
    row[model_columns.key] = item.first;
    row[model_columns.value] = item.second;
  }

  get_widget<Button> ("pluginDetailsButton")->signal_clicked ().connect ([factory_name, plugin_info]{
      std::make_shared<PluginInfoWindow> (plugin_info.get_factory_plugin (factory_name))->show_window ();
  });
}

FactoryInfoWindow::~FactoryInfoWindow ()
{
}

void FactoryInfoWindow::show_window ()
{
  window->show_now ();
}

