AM_CPPFLAGS = $(GLOBAL_CPPLAGS) \
    -I$(top_srcdir)/include


bin_PROGRAMS = macvdmtool

macvdmtool_SOURCES = macvdmtool.cpp
macvdmtool_CPPFLAGS = $(AM_CPPFLAGS)
macvdmtool_LDFLAGS = $(AM_LDFLAGS)
macvdmtool_LDADD = $(top_builddir)/src/libmacvdm-1.0.la