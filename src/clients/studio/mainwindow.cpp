#include "mainwindow.h"
#include "sigcpp_lambda_hack.h"
#include "plugininspector.h"
#include "elementitem.h"
#include "elementinfo.h"

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

    get_widget<Gtk::ToolButton> ("addElementToolButton")->signal_clicked ().connect ([this] {
      try
      {
        ElementItem::create(Gst::ElementFactory::create_element(plugins_inspector->get_selected ()),
          canvas.get_root_item ());
      }
      catch (const std::runtime_error& ex)
      {
        Logger::get_instance ()->log (ex, LogLevel::WARN);
      }
    });

    get_widget<Gtk::MenuItem> ("quitMenuItem")->signal_button_press_event ().connect ([this, logger] (GdkEventButton*) {
      get_window ()->hide ();
      return true;
    });

    TreeView *inspector_tree = get_widget<TreeView> ("pluginsInspectorTreeView");
    SearchEntry *inspector_searchbox = get_widget<SearchEntry>("searchPluginSearchEntry");
    Button *plugin_info_button = get_widget<Button>("pluginInfoButton");
    plugins_inspector = std::make_shared<PluginInspector> (inspector_tree, inspector_searchbox, plugin_info_button);

    TreeView *selected_element_tree = get_widget<TreeView> ("selectedElementTreeView");
    selected_element_info = std::make_shared<ElementInfo>(selected_element_tree);

    canvas.set_size_request(100, 100);
    canvas.set_bounds(0, 0, 1000, 1000);
    canvas.show();

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
