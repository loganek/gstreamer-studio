/*
 * elementinfo.h
 *
 *  Created on: Dec 22, 2014
 *      Author: loganek
 */

#ifndef ELEMENTINFO_H_
#define ELEMENTINFO_H_

#include "twocolumnmodel.h"
#include "utils/gstreamerutils.h"

#include <gtkmm.h>
#include <gstreamermm.h>

namespace GstreamerStudio {
namespace Clients {

class ElementInfo
{
  Gtk::TreeView* tree;
  Glib::RefPtr<Gtk::TreeStore> model;
  TwoColumnModel model_columns;

  void show_object_info(std::string str, const GstreamerStudio::Utils::ObjectNodeInfo& inf, const Gtk::TreeModel::Row* parent);

public:
  ElementInfo(Gtk::TreeView* tree);

  void update_info(const Glib::RefPtr<Gst::Object>& obj);
};

}
}

#endif /* ELEMENTINFO_H_ */
