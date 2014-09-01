/*
 * twocolumnmodel.h
 *
 *  Created on: Sep 2, 2014
 *      Author: loganek
 */

#ifndef TWOCOLUMNMODEL_H_
#define TWOCOLUMNMODEL_H_

#include <gtkmm.h>

namespace GstreamerStudio {
namespace Clients {

class TwoColumnModel : public Gtk::TreeModel::ColumnRecord
{
public:
  Gtk::TreeModelColumn<Glib::ustring> key;
  Gtk::TreeModelColumn<Glib::ustring> value;

  TwoColumnModel () { add (key); add (value); }
  virtual ~TwoColumnModel () {}
};

}
}

#endif /* TWOCOLUMNMODEL_H_ */
