#include "mainwindow.h"

#include "core/logger.h"

#include <gtkmm.h>

using namespace GstreamerStudio::Clients;

int main (int argc, char *argv[])
{
  Gst::init (argc, argv);
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create (argc, argv, "org.gtkmm.test");
  
  try
  {
    MainWindow window;

    app->run (*(window.get_window ()));
  }
  catch (const std::runtime_error& ex)
  {
    GstreamerStudio::Core::Logger::get_instance ()->log (ex, GstreamerStudio::Core::LogLevel::ERROR);
  }

  return 0;
}
