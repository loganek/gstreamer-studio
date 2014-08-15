#include <gtkmm.h>

int main (int argc, char *argv[])
{
  Gtk::ApplicationWindow* window;
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.test");
  Glib::RefPtr<Gtk::Builder> builder;
  try
    {
      builder = Gtk::Builder::create_from_file("ui/mainwindow.glade");
    }
  catch (const Glib::FileError& ex)
    {
      puts("dupa");
      // todo: error handler
      return 1;
    }
  catch (const Glib::MarkupError& ex)
    {
      // todo: error handler
      return 1;
    }
  catch (const Gtk::BuilderError& ex)
    {
      // todo: error handler
      return 1;
    }

  builder->get_widget("mainWindow", window);
  app->run(*window);
  return 0;
}
