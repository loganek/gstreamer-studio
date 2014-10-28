AC_INIT(
	[gstreamer-studio],
	[0.1],
	[https://github.com/loganek/gstreamer-studio/issues],
	[gstreamer-studio],
	[http://github.com/loganek/gstreamer-studio])

AC_PREREQ(2.69)

AC_CONFIG_AUX_DIR(build)

AM_INIT_AUTOMAKE

AM_GNU_GETTEXT_VERSION([0.18.3])
AM_GNU_GETTEXT([external])

AC_CONFIG_HEADER([src/config.h])

AC_PROG_CXX
AC_LANG([C++])
AC_LANG_COMPILER_REQUIRE

AC_PROG_RANLIB

PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0])
PKG_CHECK_MODULES([GLIBMM], [glibmm-2.4])
PKG_CHECK_MODULES([GOOCANVASMM], [goocanvasmm-2.0])
PKG_CHECK_MODULES([GSTREAMERMM], [gstreamermm-1.0])

CXXFLAGS="-Wall -Werror -std=c++11 $CXXFLAGS"

AC_CONFIG_FILES([ po/Makefile.in
	Makefile
	src/core/Makefile
	src/clients/studio/Makefile
])

AC_OUTPUT
