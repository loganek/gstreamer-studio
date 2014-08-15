#include "mainwindow.h"
#include <gtkmm.h>

using namespace GstreamerStudio::Clients;

int main (int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.test");
  
  MainWindow window;

  app->run(*(window.get_window()));
  return 0;
}
