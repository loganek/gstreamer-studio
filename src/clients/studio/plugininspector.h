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
  Gtk::TreeView* view;

  void fill_tree ();
public:
  PluginInspector (Gtk::TreeView* tree);
  virtual ~PluginInspector ();

};
}
}

#endif /* PLUGININSPECTOR_H_ */
