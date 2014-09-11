/*
 * baseproperty.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: loganek
 */

#include "baseproperty.h"

#include <gstreamermm.h>

#if _WIN32 || _WIN64
#if _WIN64
#define ENV64
#else
#define ENV32
#endif
#endif

#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENV64
#else
#define ENV32
#endif
#endif

namespace GstreamerStudio {
namespace Core {

#define NUMERIC_CASE(GTYPE, gtype, GPSType, CppType) \
  case G_TYPE_##GTYPE: \
  { \
    GParamSpec##GPSType *p_val = G_PARAM_SPEC_##GTYPE (spec); \
    property_base = new BaseProperty<CppType>  \
        (p_val->default_value, is_readable () ? g_value_get_##gtype (&value) : 0, p_val->minimum, p_val->maximum); \
    break; \
  }

#define NUMERIC_CONSTRUCTOR(type) \
template<> \
BaseProperty<type>::BaseProperty(const type& default_value, const type& value, const type& min, const type& max) \
: value (value), default_value (default_value), min (min), max (max) {}

#ifdef ENV32
NUMERIC_CONSTRUCTOR (gulong)
NUMERIC_CONSTRUCTOR (glong)
#endif
NUMERIC_CONSTRUCTOR (guint)
NUMERIC_CONSTRUCTOR (gint)
NUMERIC_CONSTRUCTOR (guint64)
NUMERIC_CONSTRUCTOR (gint64)
NUMERIC_CONSTRUCTOR (float)
NUMERIC_CONSTRUCTOR (double)

GstProperty::GstProperty (GParamSpec *param_spec)
: spec (param_spec)
{

  GValue value = {0, };
  g_value_init (&value, spec->value_type);

  switch (G_VALUE_TYPE (&value))
  {
  case G_TYPE_BOOLEAN:
  {
    GParamSpecBoolean *pboolean = G_PARAM_SPEC_BOOLEAN (param_spec);
    property_base = new BaseProperty<bool> (pboolean->default_value, is_readable () ? g_value_get_boolean (&value) : false);
    break;
  }
  case G_TYPE_STRING:
  {
    GParamSpecString *pstring = G_PARAM_SPEC_STRING (spec);
    std::string val;
    if (is_readable ())
    {
      const char *string_val = g_value_get_string (&value);
      if (string_val != nullptr)
        val = string_val;
    }
    property_base = new BaseProperty<std::string> (
        (pstring->default_value == nullptr) ? "" : pstring->default_value, val);
    break;
  }
#ifdef ENV32
  NUMERIC_CASE (ULONG, ulong, ULong, gulong)
  NUMERIC_CASE (LONG, long, Long, glong)
#endif
  NUMERIC_CASE (UINT, uint, UInt, guint)
  NUMERIC_CASE (INT, int, Int, gint)
  NUMERIC_CASE (UINT64, uint64, UInt64, guint64)
  NUMERIC_CASE (INT64, int64, Int64, gint64)
  NUMERIC_CASE (FLOAT, float, Float, float)
  NUMERIC_CASE (DOUBLE, double, Double, double)
  }
}

GstProperty::~GstProperty ()
{
  delete property_base;
  property_base = nullptr;
}

std::string GstProperty::get_name () const
{
  return g_param_spec_get_name (spec);
}

std::string GstProperty::get_description () const
{
  return g_param_spec_get_blurb (spec);
}

#define GENERATE_FLAG_ACCESSOR(ABILITY, FLAG) \
bool GstProperty::is_##ABILITY () const \
{ \
  return spec->flags & FLAG; \
}

GENERATE_FLAG_ACCESSOR (readable, G_PARAM_READABLE)
GENERATE_FLAG_ACCESSOR (writable, G_PARAM_WRITABLE)
GENERATE_FLAG_ACCESSOR (controllable, GST_PARAM_CONTROLLABLE)
GENERATE_FLAG_ACCESSOR (mutable_playing, GST_PARAM_MUTABLE_PLAYING)
GENERATE_FLAG_ACCESSOR (mutable_paused, GST_PARAM_MUTABLE_PAUSED)
GENERATE_FLAG_ACCESSOR (mutable_ready, GST_PARAM_MUTABLE_READY)

}
}
