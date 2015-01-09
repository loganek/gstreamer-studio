bin_PROGRAMS = gstreamer-studio-test

gstreamer_studio_test_SOURCES = \
							maintest.cpp \
							leparxer/lexer.cpp

gstreamer_studio_test_CPPFLAGS = $(GTKMM_CFLAGS) $(GOOCANVASMM_CFLAGS) $(GSTREAMERMM_CFLAGS) -I../src -DLOCALEDIR=\"$(localedir)\"
gstreamer_studio_test_LDADD = -lpthread -lgtest -lgtest_main \
							-L../src/core -lgstreamer-studio-core \
							-L../src/utils -lgstreamer-studio-utils \
							-L../src/leparxer -lgstreamer-studio-leparxer \
							$(GSTREAMERMM_LIBS) $(GOOCANVASMM_LIBS) $(GTKMM_LIBS) $(LIBINTL)

