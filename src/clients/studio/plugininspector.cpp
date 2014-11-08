#include "plugininspector.h"
#include "sigcpp_lambda_hack.h"
#include "plugininfowindow.h"
#include "factoryinfowindow.h"

#include "core/logger.h"
#include "core/plugininfo.h"

using namespace GstreamerStudio::Clients;
using namespace Gtk;
using GstreamerStudio::Core::LogLevel;


PluginInspector::PluginInspector (TreeView* tree, SearchEntry *searchbox)
: view (tree),
  searchbox(searchbox)
{
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

    if (!it->parent ())
    {
      std::make_shared<PluginInfoWindow> (plugin_name)->show_window ();
    }
    else if (it->children ().empty ())
    {
      std::make_shared<FactoryInfoWindow> (plugin_name)->show_window ();
    }
  });

  model = TreeStore::create(model_columns);

  auto filter = Gtk::TreeModelFilter::create(model);
  filter->set_visible_func(sigc::mem_fun(*this, &PluginInspector::filter_func));
  tree->append_column("Plugin", model_columns.plugin_name);
  tree->set_model (filter);

  fill_tree ();

  searchbox->signal_changed().connect([filter]{filter->refilter();});
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

bool PluginInspector::check_children_filter (TreeModel::iterator& it)
{
  int cnt = 0;
  do {
    Glib::ustring data;
    it->get_value (0, data);

    if (searchbox->get_text () == data.substr(0, searchbox->get_text ().size ()))
      cnt++;
    else if (it->children().size () > 0)
      cnt += check_children_filter (++it);
  } while (++it);

  return cnt > 0;
}

bool PluginInspector::filter_func (const TreeModel::iterator& it)
{
  Glib::ustring data;
  it->get_value(0, data);
  if (searchbox->get_text () == data.substr (0, searchbox->get_text ().size ()))
    return true;
  else if(it->children().size() > 0)
  {
    auto i = const_cast<TreeModel::iterator&> (it)->children ().begin ();
	  return check_children_filter (i);
  }
  return false;
}

PluginInspector::PluginsModelColumns::PluginsModelColumns ()
{
  add(plugin_name);
}

Glib::ustring PluginInspector::get_selected () const
{
  auto rows = view->get_selection ()->get_selected_rows ();

  if (rows.size () == 0)
    throw std::runtime_error ("no item selected");

  Glib::ustring selected;
  model->get_iter (rows.front ())->get_value (0, selected);

  return selected;

}
