## Process Makefile.am with automake to create Makefile.in. -*- Makefile -*-
## Written by Andreas Ferber <sunshine@bielefeld.ccc.de>

INCLUDES = -I$(top_srcdir)/include $(CPPUNIT_CFLAGS)
LDADD = ../../src/libcccp/libcccp.la $(CPPUNIT_LIBS)

if HAVE_CPPUNIT
TESTS = libcccp_test
check_PROGRAMS = $(TESTS)
endif

libcccp_test_SOURCES = \
	main.cpp	\
	objecttest.cpp

# vim:ft=make
