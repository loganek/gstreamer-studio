/*
 * factoryinfowindow.h
 *
 *  Created on: Sep 2, 2014
 *      Author: loganek
 */

#ifndef FACTORYINFOWINDOW_H_
#define FACTORYINFOWINDOW_H_

#include "buildablegtk.h"
#include "twocolumnmodel.h"

#include <gtkmm.h>

namespace GstreamerStudio {
namespace Clients {

class FactoryInfoWindow : BuildableGtk
{
private:
  Gtk::Window* window = nullptr;

  TwoColumnModel model_columns;

public:
  FactoryInfoWindow (const std::string& factory_name);
  virtual ~FactoryInfoWindow ();

  void show_window ();
};

}
}

#endif /* FACTORYINFOWINDOW_H_ */
