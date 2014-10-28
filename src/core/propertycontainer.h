/*
 * propertycontainer.h
 *
 *  Created on: Sep 7, 2014
 *      Author: loganek
 */

#ifndef CORE_PROPERTYCONTAINER_H
#define CORE_PROPERTYCONTAINER_H

#include "baseproperty.h"

#include <gstreamermm.h>

#include <memory>

namespace GstreamerStudio {
namespace Core {

class PropertyContainer
{
private:
  Glib::RefPtr<Gst::Element> element;

  std::vector<std::shared_ptr<GstProperty>> properties;

  void init ();

public:
  PropertyContainer (const std::string& factory_name);
  PropertyContainer (Glib::RefPtr<Gst::Element> element);
  virtual ~PropertyContainer ();

  std::vector<std::shared_ptr<GstProperty>> get_properties () const;
};

}
}

#endif
