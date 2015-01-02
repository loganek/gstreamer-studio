#include "mainwindow.h"

#include "core/logger.h"
#include "core/controller.h"

#include <gtkmm.h>

#include "config.h"
#include "gettext.h"
#include <locale.h>

using namespace GstreamerStudio::Clients;
using namespace GstreamerStudio::Core;

int main (int argc, char *argv[])
{
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);
  bind_textdomain_codeset(PACKAGE, "utf-8");
  std::shared_ptr<Controller> controller = std::make_shared<Controller>("main-model");
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create (argc, argv, "org.gtkmm.test");
  Logger::get_instance ()->set_debug_level (LogLevel::INFO);
  
  try
  {
    MainWindow window;
    controller->set_gui(&window);
    window.set_controller(controller);
    app->run (*(window.get_window ()));
  }
  catch (const std::runtime_error& ex)
  {
    Logger::get_instance ()->log (ex, GstreamerStudio::Core::LogLevel::ERROR);
  }

  return 0;
}
