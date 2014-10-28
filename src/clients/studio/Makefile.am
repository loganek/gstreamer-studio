bin_PROGRAMS = gstreamer-studio

gstreamer_studio_SOURCES = \
							mainwindow.cpp \
							gstreamer-studio.cpp \
							plugininspector.cpp \
							plugininfowindow.cpp \
							factoryinfowindow.cpp \
							elementitem.cpp \
							paditem.cpp

gstreamer_studio_CPPFLAGS = $(GTKMM_CFLAGS) $(GOOCANVASMM_CFLAGS) $(GSTREAMERMM_CFLAGS) -I../../ -DLOCALEDIR=\"$(localedir)\"
gstreamer_studio_LDADD =  -L../../core -lgstreamer-studio-core $(GSTREAMERMM_LIBS) $(GOOCANVASMM_LIBS) $(GTKMM_LIBS) $(LIBINTL)

