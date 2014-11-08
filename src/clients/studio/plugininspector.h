#ifndef PLUGININSPECTOR_H_
#define PLUGININSPECTOR_H_

#include <gtkmm.h>

namespace GstreamerStudio {

namespace Core {
class Logger;
class PluginInfo;
}

namespace Clients {

class PluginInspector
{
private:
  GstreamerStudio::Core::Logger *logger;
  GstreamerStudio::Core::PluginInfo *plugin_info;

  class PluginsModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:
    Gtk::TreeModelColumn<Glib::ustring> plugin_name;

    PluginsModelColumns ();
    virtual ~PluginsModelColumns () {}
  };

  PluginsModelColumns model_columns;
  Glib::RefPtr<Gtk::TreeStore> model;
  Gtk::TreeView *view;
  Gtk::SearchEntry *searchbox;

  void fill_tree ();
  bool filter_func(const Gtk::TreeModel::const_iterator& it);
  bool check_children_filter (Gtk::TreeModel::iterator& it);

public:
  PluginInspector (Gtk::TreeView *tree, Gtk::SearchEntry *searchbox);
  virtual ~PluginInspector ();

  Glib::ustring get_selected () const;

};
}
}

#endif /* PLUGININSPECTOR_H_ */
