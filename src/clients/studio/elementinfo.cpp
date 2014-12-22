/*
 * elementinfo.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: loganek
 */

#include "elementinfo.h"
#include "utils/gstreamerutils.h"
#include "gettext.h"

using namespace GstreamerStudio::Clients;
using namespace Gtk;

ElementInfo::ElementInfo(TreeView* tree)
: tree(tree)
{
  model = TreeStore::create(model_columns);
  auto filter = Gtk::TreeModelFilter::create(model);
  tree->append_column("Key", model_columns.key);
  tree->append_column("Value", model_columns.value);
  tree->set_model (filter);
  update_info(Gst::ElementFactory::create_element("videotestsrc")->get_static_pad("src"));
}

void ElementInfo::update_info(const Glib::RefPtr<Gst::Object>& obj)
{
  model->clear();

  for (auto i : GstreamerStudio::Utils::GstreamerUtils::get_object_info(obj))
    show_object_info(i.first, i.second, nullptr);
}

void ElementInfo::show_object_info(std::string str, const GstreamerStudio::Utils::ObjectNodeInfo& inf, const TreeModel::Row* parent)
{
  TreeModel::Row row = parent == nullptr ? *(model->append ()) : *(model->append (parent->children ()));
  row[model_columns.key] = str;
  row[model_columns.value] = inf.get_value();

  for (auto i : inf.get_map())
    show_object_info(i.first, i.second, &row);
}
