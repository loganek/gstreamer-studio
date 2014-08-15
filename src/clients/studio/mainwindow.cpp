#include "mainwindow.h"

using namespace GstreamerStudio::Clients;
using namespace Gtk;
using namespace Glib;

MainWindow::MainWindow ()
{
  try
    {
      builder = Builder::create_from_file ("ui/mainwindow.glade");
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
}

MainWindow::~MainWindow ()
{
  delete window;
}

Gtk::ApplicationWindow* MainWindow::get_window ()
{
  if (window == nullptr)
    {
      builder->get_widget("mainWindow", window);
    }

  return window;
}
