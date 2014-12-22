bin_PROGRAMS = gstreamer-studio

gstreamer_studio_SOURCES = \
							mainwindow.cpp \
							gstreamer-studio.cpp \
							plugininspector.cpp \
							plugininfowindow.cpp \
							factoryinfowindow.cpp \
							elementitem.cpp \
							paditem.cpp \
							linkitem.cpp \
							elementinfo.cpp

gstreamer_studio_CPPFLAGS = $(GTKMM_CFLAGS) $(GOOCANVASMM_CFLAGS) $(GSTREAMERMM_CFLAGS) -I../../ -DLOCALEDIR=\"$(localedir)\"
gstreamer_studio_LDADD =  -L../../core -lgstreamer-studio-core -L../../utils -lgstreamer-studio-utils $(GSTREAMERMM_LIBS) $(GOOCANVASMM_LIBS) $(GTKMM_LIBS) $(LIBINTL)

