#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <gtkmm.h>

#include <memory>

namespace GstreamerStudio {
namespace Clients {

class PluginInspector;

class MainWindow
{
private:
  Glib::RefPtr<Gtk::Builder> builder;
  Gtk::ApplicationWindow* window = nullptr;
  std::shared_ptr<PluginInspector> plugins_inspector;

  template<typename T>
  T* get_widget (const Glib::ustring& name)
  {
    T* widget = nullptr;
    builder->get_widget<T> (name, widget);

    if (widget == nullptr)
    {
      throw std::runtime_error ("cannot get " + name + " widget");
    }

    return widget;
  }

 public:
  MainWindow ();
  virtual ~MainWindow ();
  
  Gtk::ApplicationWindow* get_window ();
};

}
}

#endif
