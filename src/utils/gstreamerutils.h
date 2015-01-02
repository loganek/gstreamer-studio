/*
 * gstreamerutils.h
 *
 *  Created on: Dec 22, 2014
 *      Author: loganek
 */

#ifndef GSTREAMERUTILS_H_
#define GSTREAMERUTILS_H_

#include <gstreamermm.h>

#include <map>

namespace GstreamerStudio {
namespace Utils {

class ObjectNodeInfo
{
public:
  typedef std::map<std::string, ObjectNodeInfo> MapInfo;
private:
  std::string value;
  MapInfo info_map;
public:
  ObjectNodeInfo() {}
  ObjectNodeInfo (const std::string& value) : value(value) {}
  std::string get_value() const { return value; }
  void insert(const std::string& key, const ObjectNodeInfo& obj)
  { info_map.insert({key, obj}); }
  MapInfo get_map() const { return info_map; }
};

class GstreamerUtils
{
private:
  static ObjectNodeInfo::MapInfo parse_pad_template(const Glib::RefPtr<Gst::PadTemplate>& tpl);
  static ObjectNodeInfo parse_caps(const Glib::RefPtr<Gst::Caps>& caps);
public:
  static std::map<std::string, ObjectNodeInfo> get_object_info(const Glib::RefPtr<Gst::Object>& object);
  static std::vector<std::string> get_path(const Glib::RefPtr<Gst::Object>& obj);
  static Glib::RefPtr<Gst::Object> find_element(std::vector<std::string> path,
    const Glib::RefPtr<Gst::Element>& model);
};

}
}


#endif /* GSTREAMERUTILS_H_ */
