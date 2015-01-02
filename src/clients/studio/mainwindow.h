#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include "buildablegtk.h"
#include "iselectableobserver.h"

#include "core/IGui.h"

#include <gtkmm.h>
#include <goocanvasmm-2.0/goocanvasmm.h>

#include <memory>

namespace GstreamerStudio {
namespace Clients {

class PluginInspector;
class ElementInfo;

class MainWindow : public BuildableGtk, public Core::IGui, public ISelectableObserver
{
private:
  Gtk::ApplicationWindow* window = nullptr;
  std::shared_ptr<Core::Controller> controller;
  std::shared_ptr<PluginInspector> plugins_inspector;
  std::shared_ptr<ElementInfo> selected_element_info;
  Goocanvas::Canvas canvas;

  void selection_changed (Core::IObservable<ISelectableObserver>* sender, const Glib::RefPtr<Gst::Object>& selected) override;

public:
  MainWindow ();
  virtual ~MainWindow ();
  
  Gtk::ApplicationWindow* get_window ();
  void set_controller(std::shared_ptr<Core::Controller> controller) override
  {
    this->controller = controller;
  }

  void current_model_changed (const std::string& path) override;
};

}
}

#endif
