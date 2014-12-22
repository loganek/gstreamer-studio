#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include "buildablegtk.h"

#include <gtkmm.h>
#include <goocanvasmm-2.0/goocanvasmm.h>

#include <memory>

namespace GstreamerStudio {
namespace Clients {

class PluginInspector;
class ElementInfo;

class MainWindow : public BuildableGtk
{
private:
  Gtk::ApplicationWindow* window = nullptr;
  std::shared_ptr<PluginInspector> plugins_inspector;
  std::shared_ptr<ElementInfo> selected_element_info;
  Goocanvas::Canvas canvas;

public:
  MainWindow ();
  virtual ~MainWindow ();
  
  Gtk::ApplicationWindow* get_window ();
};

}
}

#endif
