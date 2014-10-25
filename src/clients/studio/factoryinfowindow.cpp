/*
 * factoryinfowindow.cpp
 *
 *  Created on: Sep 2, 2014
 *      Author: loganek
 */

#include "factoryinfowindow.h"
#include "plugininfowindow.h"

#include "core/plugininfo.h"
#include "core/propertycontainer.h"

#include "gettext.h"

using namespace GstreamerStudio;
using namespace GstreamerStudio::Clients;
using namespace Gtk;

FactoryInfoWindow::FactoryInfoWindow (const std::string& factory_name)
{
  builder = Builder::create_from_file ("src/clients/studio/ui/plugininfo.glade");

  builder->get_widget<Gtk::Window> ("elementInfoWindow", window);

  Glib::RefPtr<ListStore> model = ListStore::create (model_columns);
  TreeView *tree = get_widget<TreeView> ("metadataTreeView");

  tree->append_column(_("Key"), model_columns.key);
  tree->append_column(_("Value"), model_columns.value);
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

  Glib::RefPtr<ListStore> properties_model = ListStore::create (properties_model_columns);
  TreeView *props_tree = get_widget<TreeView> ("propertiesTreeView");

  props_tree->append_column(_("Property"), properties_model_columns.key);
  props_tree->append_column(_("Value"), properties_model_columns.value);
  props_tree->set_model (properties_model);

  Core::PropertyContainer props(Gst::ElementFactory::create_element(factory_name));

  for (auto property : props.get_properties())
  {
    TreeModel::Row row = *(properties_model->append());
    row[properties_model_columns.key] = property->get_name();
    row[properties_model_columns.value] = property->get_description();
  }
}

FactoryInfoWindow::~FactoryInfoWindow ()
{
}

void FactoryInfoWindow::show_window ()
{
  window->show_now ();
}

