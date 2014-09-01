/*
 * plugininfo.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: loganek
 */

#include "plugininfo.h"

namespace GstreamerStudio {
namespace Core {

PluginTreeItem::PluginTreeItem (const std::string& element_name)
: element_name (element_name)
{}

std::string PluginTreeItem::get_name () const
{
  return element_name;
}

std::vector<PluginTreeItem> PluginTreeItem::get_children () const
{
  return children;
}

void PluginTreeItem::add_child (const PluginTreeItem& child)
{
  children.push_back (child);
}

PluginInfo::PluginInfo ()
: registry (Gst::Registry::get ())
{
}

template<>
std::vector<PluginTreeItem> PluginInfo::get_elements<ElementSortMethod::BY_PLUGIN> () const
{
  return get_elements_by_plugin ();
}

template<>
std::vector<PluginTreeItem> PluginInfo::get_elements<ElementSortMethod::BY_CATEGORY> () const
{
  return get_elements_by_class ();
}

std::vector<PluginTreeItem> PluginInfo::get_elements_by_plugin () const
{
  std::vector<PluginTreeItem> items;

  for (Glib::RefPtr<Gst::Plugin> plugin : registry->get_plugin_list ())
  {
    items.push_back (PluginTreeItem (plugin->get_name ()));

    for (auto feature : registry->get_feature_list (plugin->get_name ()))
    {
      if (feature && GST_IS_ELEMENT_FACTORY (feature->gobj ()))
        items.back ().add_child (PluginTreeItem (feature->get_name ()));
    }
  }

  return items;
}

std::vector<PluginTreeItem> PluginInfo::get_elements_by_class () const
{
  std::vector<PluginTreeItem> items;

  for (Glib::RefPtr<Gst::Plugin> plugin : registry->get_plugin_list ())
  {
    // todo
  }

  return items;
}

// used vector<pair<>> instead of map, because of undesirable sorting by key in std::map
PluginInfo::unsorted_map PluginInfo::get_plugin_info (const std::string& plugin_name) const
{
  Glib::RefPtr<Gst::Plugin> plugin = Gst::Plugin::load_by_name (plugin_name);

  if (!plugin)
  {
    throw std::runtime_error ("unknown plugin: " + plugin_name);
  }

  unsorted_map plugin_info = {
      std::make_pair ("Name", plugin->get_name ()),
      std::make_pair ("Description", plugin->get_description ()),
      std::make_pair ("Filename", plugin->get_filename ()),
      std::make_pair ("Version", plugin->get_version ()),
      std::make_pair ("License", plugin->get_license ()),
      std::make_pair ("Source module", plugin->get_source ()),
      std::make_pair ("Source release date", plugin->get_release_date_string ()),
      std::make_pair ("Binary package", plugin->get_package ()),
      std::make_pair ("Origin URL", plugin->get_origin ())
  };

  return plugin_info;
}

PluginInfo::unsorted_map PluginInfo::get_factory_metadata (const std::string& factory_name) const
{
  Glib::RefPtr<Gst::ElementFactory> factory = Gst::ElementFactory::find (factory_name);

  if (!factory)
  {
    throw std::runtime_error ("unknown element factory: " + factory_name);
  }

  unsorted_map factory_meta;

  for (auto key : factory->get_metadata_keys ())
  {
    factory_meta.push_back (std::make_pair (key, factory->get_metadata (key)));
  }

  return factory_meta;
}

std::string PluginInfo::get_factory_plugin (const std::string& factory_name) const
{
  Glib::RefPtr<Gst::ElementFactory> factory = Gst::ElementFactory::find (factory_name);
  Glib::RefPtr<Gst::Plugin> plugin = factory->get_plugin ();

  if (!plugin)
  {
    throw std::runtime_error ("cannot get plugin of factory " + factory_name);
  }

  return plugin->get_name ();
}

}
}
