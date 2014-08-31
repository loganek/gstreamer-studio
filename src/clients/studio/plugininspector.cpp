#include "plugininspector.h"
#include "sigcpp_lambda_hack.h"

#include "core/logger.h"
#include "core/plugininfo.h"

using namespace GstreamerStudio::Clients;
using namespace Gtk;
using GstreamerStudio::Core::LogLevel;

PluginInspector::PluginInspector (TreeView* tree)
: view (tree)
{
  Gst::init();
  logger = GstreamerStudio::Core::Logger::get_instance ();
  plugin_info = new GstreamerStudio::Core::PluginInfo ();

  view->signal_row_activated ().connect ([this] (const TreeModel::Path& path, TreeViewColumn*) {
    TreeModel::iterator it = view->get_model ()->get_iter (path);

    if (!it)
    {
      return;
    }

    Glib::ustring plugin_name;
    it->get_value (0, plugin_name);
    logger->log ("Selected plugin " + plugin_name, LogLevel::INFO);
  });

  model = TreeStore::create(model_columns);

  tree->append_column("Plugin", model_columns.plugin_name);
  tree->set_model (model);

  fill_tree ();
}

PluginInspector::~PluginInspector ()
{
	delete plugin_info;
}

void PluginInspector::fill_tree()
{
  for (GstreamerStudio::Core::PluginTreeItem item : plugin_info->get_elements<GstreamerStudio::Core::ElementSortMethod::BY_PLUGIN> ())
  {
    TreeModel::Row row = *(model->append ());
    row[model_columns.plugin_name] = item.get_name ();

    for (GstreamerStudio::Core::PluginTreeItem items : item.get_children ())
    {
      TreeIter rw = model->append(row.children());
      (*rw)[model_columns.plugin_name] = items.get_name();
    }
  }
}

PluginInspector::PluginsModelColumns::PluginsModelColumns ()
{
  add(plugin_name);
}
