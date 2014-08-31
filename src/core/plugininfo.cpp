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

}
}
