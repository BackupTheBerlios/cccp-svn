## Process Makefile.am with automake to create Makefile.in. -*- Makefile -*-
## Written by Andreas Ferber <sunshine@bielefeld.ccc.de>

lib_LTLIBRARIES = libcccp.la

libcccp_la_SOURCES = object.cpp mainloop.cpp
libcccp_la_LDFLAGS = @BOOST_LDFLAGS@
libcccp_la_LIBADD = -lboost_signals

AM_CPPFLAGS = -I$(top_srcdir)/include @BOOST_CPPFLAGS@

# vim:ft=make
