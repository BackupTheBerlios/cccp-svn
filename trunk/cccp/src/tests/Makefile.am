## Process Makefile.am with automake to create Makefile.in. -*- Makefile -*-
## Written by Andreas Ferber <sunshine@bielefeld.ccc.de>

noinst_PROGRAMS = testobject

AM_CPPFLAGS = -I$(top_srcdir)/include @BOOST_CPPFLAGS@

testobject_SOURCES = testobject.cpp
testobject_LDFLAGS = @BOOST_LDFLAGS@
testobject_LDADD = ../libcccp/libcccp.la -lboost_signals

# vim:ft=make
