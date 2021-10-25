AM_CPPFLAGS = \
    -I$(top_srcdir)/include \
	$(GLOBAL_CPPFLAGS) \
    -std=c++14

AM_LDFLAGS = \
	$(GLOBAL_LDFLAGS) \
    -framework CoreFoundation \
    -framework IOKit \
    -lc++

lib_LTLIBRARIES = libmacvdm-1.0.la
libmacvdm_1_0_la_CPPFLAGS = $(AM_CPPFLAGS)
libmacvdm_1_0_la_LDFLAGS = $(AM_LDFLAGS) -version-info 1 -dynamic
libmacvdm_1_0_la_SOURCES = macvdm.cpp