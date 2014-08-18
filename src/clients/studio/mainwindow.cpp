#include "mainwindow.h"
#include "sigcpp_lambda_hack.h"

using namespace GstreamerStudio::Clients;
using namespace Gtk;
using namespace Glib;

MainWindow::MainWindow ()
{
  try
  {
    builder = Builder::create_from_file ("src/clients/studio/ui/mainwindow.glade");

    get_widget<Gtk::MenuItem> ("aboutMenuItem")->signal_button_press_event ().connect ([this] (GdkEventButton*) {
      Gtk::AboutDialog* about = get_widget<Gtk::AboutDialog> ("aboutDialog");
      about->run ();
      about->close ();
      return true;
    });
  }
  catch (const FileError& ex)
  {
    // todo: error handler
  }
  catch (const MarkupError& ex)
  {
    // todo: error handler
  }
  catch (const BuilderError& ex)
  {
    // todo: error handler
  }
  catch (const std::runtime_error& ex)
  {
    // todo: error handler (get_widget)
  }
}

MainWindow::~MainWindow ()
{
  delete window;
}

Gtk::ApplicationWindow* MainWindow::get_window ()
{
  if (window == nullptr)
  {
    builder->get_widget<Gtk::ApplicationWindow> ("mainWindow", window);
  }

  return window;
}
