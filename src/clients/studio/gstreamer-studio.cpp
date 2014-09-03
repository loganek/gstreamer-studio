#include "mainwindow.h"

#include "core/logger.h"

#include <gtkmm.h>
#include <gstreamermm.h>

#include "config.h"
#include "gettext.h"
#include <locale.h>

using namespace GstreamerStudio::Clients;
using namespace GstreamerStudio::Core;

int main (int argc, char *argv[])
{
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  puts (LOCALEDIR);
  textdomain (PACKAGE);
  bind_textdomain_codeset(PACKAGE, "utf-8");
  Gst::init (argc, argv);
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create (argc, argv, "org.gtkmm.test");
  Logger::get_instance ()->set_debug_level (LogLevel::INFO);
  
  try
  {
    MainWindow window;

    app->run (*(window.get_window ()));
  }
  catch (const std::runtime_error& ex)
  {
    Logger::get_instance ()->log (ex, GstreamerStudio::Core::LogLevel::ERROR);
  }

  return 0;
}
