/*
 * plugininfowindow.h
 *
 *  Created on: Aug 31, 2014
 *      Author: loganek
 */

#ifndef PLUGININFOWINDOW_H_
#define PLUGININFOWINDOW_H_

#include "buildablegtk.h"
#include "twocolumnmodel.h"

#include <gtkmm.h>

namespace GstreamerStudio {
namespace Clients {

class PluginInfoWindow : BuildableGtk
{
private:
  Gtk::Window* window = nullptr;

  TwoColumnModel model_columns;

public:
  PluginInfoWindow (const std::string& plugin_name);
  virtual ~PluginInfoWindow ();

  void show_window ();
};

}
}

#endif /* PLUGININFOWINDOW_H_ */
