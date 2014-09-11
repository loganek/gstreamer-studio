/*
 * propertycontainer.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: loganek
 */

#include "propertycontainer.h"

using namespace GstreamerStudio::Core;

PropertyContainer::PropertyContainer (const std::string& factory_name)
{
  element = Gst::ElementFactory::create_element (factory_name);
  init ();
}
PropertyContainer::PropertyContainer (const Glib::RefPtr<Gst::Element>& element)
: element (element)
{
  init ();
}

PropertyContainer::~PropertyContainer ()
{
}

void PropertyContainer::init ()
{
  guint num_properties;

  GParamSpec **property_specs = g_object_class_list_properties (G_OBJECT_GET_CLASS (element->gobj ()), &num_properties);

  for (guint i = 0; i < num_properties; i++)
  {
    properties.push_back (std::make_shared<GstProperty> (property_specs[i]));
  }
}

std::vector<std::shared_ptr<GstProperty>> PropertyContainer::get_properties () const
{
  return properties;
}

