#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <gtkmm.h>

namespace GstreamerStudio {
namespace Clients {
  
class MainWindow
{
  Glib::RefPtr<Gtk::Builder> builder;
  Gtk::ApplicationWindow* window = nullptr;

 public:
  MainWindow ();
  virtual ~MainWindow ();
  
  Gtk::ApplicationWindow* get_window ();
};

}
}

#endif
