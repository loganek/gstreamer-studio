bin_PROGRAMS = gstreamer-studio

gstreamer_studio_SOURCES = \
							mainwindow.cpp \
							gstreamer-studio.cpp \
							plugininspector.cpp \
							plugininfowindow.cpp \
							factoryinfowindow.cpp

gstreamer_studio_CPPFLAGS = $(GTKMM_CFLAGS) $(GSTREAMERMM_CFLAGS) -I../../
gstreamer_studio_LDADD =  -L../../core -lgstreamer-studio-core $(GSTREAMERMM_LIBS) $(GTKMM_LIBS)

