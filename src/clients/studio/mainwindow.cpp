#include "mainwindow.h"
#include "sigcpp_lambda_hack.h"
#include "plugininspector.h"
#include "elementitem.h"

#include "core/logger.h"

using namespace GstreamerStudio::Clients;
using namespace GstreamerStudio::Core;
using namespace Gtk;
using namespace Glib;

MainWindow::MainWindow ()
{
  Logger* logger = Logger::get_instance ();
  bool build_ok = true;

  try
  {
    builder = Builder::create_from_file ("src/clients/studio/ui/mainwindow.glade");

    get_widget<Gtk::MenuItem> ("aboutMenuItem")->signal_button_press_event ().connect ([this] (GdkEventButton*) {
      Gtk::AboutDialog* about = get_widget<Gtk::AboutDialog> ("aboutDialog");
      about->run ();
      about->close ();
      return true;
    });

    get_widget<Gtk::MenuItem> ("quitMenuItem")->signal_button_press_event ().connect ([this, logger] (GdkEventButton*) {
      get_window ()->hide ();
      return true;
    });

    TreeView *inspector_tree = get_widget<TreeView> ("pluginsInspectorTreeView");
    SearchEntry *inspector_searchbox = get_widget<SearchEntry>("searchPluginSearchEntry");
    plugins_inspector = std::make_shared<PluginInspector> (inspector_tree, inspector_searchbox);
    canvas.set_size_request(100, 100);
    canvas.set_bounds(0, 0, 1000, 1000);
    canvas.show();

    auto c = ElementItem::create(Gst::ElementFactory::create_element("identity", "i"), canvas.get_root_item ());
    get_widget<ScrolledWindow>("canvasScrolledWindow")->add(canvas);
  }
  catch (const FileError& ex)
  {
    logger->log (ex, LogLevel::ERROR);
    build_ok = false;
  }
  catch (const MarkupError& ex)
  {
    logger->log (ex, LogLevel::ERROR);
    build_ok = false;
  }
  catch (const BuilderError& ex)
  {
    logger->log (ex, LogLevel::ERROR);
    build_ok = false;
  }
  catch (const std::runtime_error& ex)
  {
    logger->log (ex, LogLevel::ERROR);
    build_ok = false;
  }

  if (!build_ok)
  {
    throw std::runtime_error ("cannot create application's main window");
  }
}

MainWindow::~MainWindow ()
{
}

Gtk::ApplicationWindow* MainWindow::get_window ()
{
  if (window == nullptr)
  {
    builder->get_widget<Gtk::ApplicationWindow> ("mainWindow", window);
  }

  return window;
}
