/*
 * plugininfo.h
 *
 *  Created on: Aug 31, 2014
 *      Author: loganek
 */

#ifndef PLUGININFO_H_
#define PLUGININFO_H_

#include <gstreamermm.h>

#include <string>
#include <vector>
#include <utility>

namespace GstreamerStudio {
namespace Core {

enum class ElementSortMethod
{
	BY_PLUGIN,
	BY_CATEGORY
};

class PluginTreeItem
{
private:
  std::string element_name;
  std::vector<PluginTreeItem> children;

public:
  PluginTreeItem (const std::string& element_name);

  std::string get_name () const;
  std::vector<PluginTreeItem> get_children () const;
  void add_child (const PluginTreeItem& child);
};

class PluginInfo
{
private:
  Glib::RefPtr<Gst::Registry> registry;

  std::vector<PluginTreeItem> get_elements_by_class () const;
  std::vector<PluginTreeItem> get_elements_by_plugin () const;
public:
  typedef std::vector<std::pair<std::string, std::string>> unsorted_map;

  PluginInfo ();

  template<ElementSortMethod sort_method>
  std::vector<PluginTreeItem> get_elements () const;

  unsorted_map get_plugin_info (const std::string& plugin_name) const;

  unsorted_map get_factory_metadata (const std::string& factory_name) const;
  std::string get_factory_plugin (const std::string& factory_name) const;
};

}
}

#endif /* PLUGININFO_H_ */
