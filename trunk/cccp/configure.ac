#                                               -*- Autoconf -*-
# $Id$
# Process this file with autoconf to produce a configure script.

AC_REVISION($Revision$)

AC_PREREQ(2.59)
AC_INIT([cccp], [0.0.1], [cryptophon@bielefeld.ccc.de])

AC_CONFIG_AUX_DIR(admin)

AC_CONFIG_SRCDIR([include/config.h.in])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 src/Makefile
                 src/libcccp/Makefile
                 src/tests/Makefile
                 tests/Makefile
                 tests/libcccp/Makefile])
AC_CONFIG_HEADER([include/config.h])

AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX

AC_COMPILE_WARNINGS

AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AC_ENABLE_SHARED(yes)
AC_ENABLE_STATIC(no)
AC_PROG_LIBTOOL

dnl We are dealing with a C++ project, so do the rest of the tests using
dnl the C++ compiler
AC_LANG(C++)

AC_CXX_NAMESPACES
if test "$ac_cv_cxx_namespaces" != yes; then
  AC_MSG_ERROR([[***
*** Your C++ compiler lacks support for namespaces.
***]])
fi

AC_CXX_HAVE_STL
if test "$ac_cv_cxx_have_stl" != yes; then
  AC_MSG_ERROR([[***
*** No suitable implementation of the Standard Template Library found.
***]])
fi

AC_CXX_EXCEPTIONS
if test "$ac_cv_cxx_exceptions" != yes; then
  AC_MSG_ERROR([[***
*** Your C++ compiler doesn't support exceptions.
***]])
fi

# Checks for libraries.
AC_DEFUN([CCC_BOOST_NOT_FOUND], [
  AC_MSG_ERROR([[***
*** Could not find Boost libraries.  Please install them first and rerun
*** configure.  See http://www.boost.org/ for more information.
***]])])

AC_ARG_WITH([boost],
  AS_HELP_STRING([--with-boost@<:@=DIR@:>@],
                 [root directory of boost installation]),
  with_boost="$withval"
  if test x"$with_boost" != yes; then
    boost_include="$withval/include"
    boost_libdir="$withval/lib"
  fi)
AC_ARG_WITH([boost-include],
  AS_HELP_STRING([--with-boost-include=DIR],
                 [specify exact include dir for boost headers]),
  [boost_include="$withval"])
AC_ARG_WITH([boost-libdir],
  AS_HELP_STRING([--with-boost-libdir=DIR],
                 [specify exact library dir for boost libraries]),
  [boost_libdir="$withval"])

if test x"$with_boost" = xno; then
  AC_MSG_ERROR([[***
*** Disabling usage of Boost libraries is not supported by this package.
***]])
fi

OLD_LDFLAGS="$LDFLAGS"
OLD_CPPFLAGS="$CPPFLAGS"

BOOST_CPPFLAGS=
BOOST_LDFLAGS=

if test x"$boost_include" != x; then
  BOOST_CPPFLAGS="-I$boost_include"
  CPPFLAGS="$CPPFLAGS -I$boost_include"
fi
if test x"$boost_libdir" != x; then
  BOOST_LDFLAGS="-L$boost_libdir"
  LDFLAGS="$LDFLAGS -L$boost_libdir"
fi

AC_CHECK_HEADERS([boost/signal.hpp boost/bind.hpp],
                 [], [[CCC_BOOST_NOT_FOUND]])
AC_CACHE_CHECK([for boost::signal in -lboost_signals],
  [ccc_cv_have_libboost_signals], [
    OLD_LIBS="$LIBS"
    LIBS="-lboost_signals $LIBS"
    AC_LINK_IFELSE(AC_LANG_PROGRAM([[#include <boost/signal.hpp>]],
                                   [[boost::signal<void ()> s;]]),
      [ccc_cv_have_libboost_signals=yes],
      [ccc_cv_have_libboost_signals=no])
    LIBS="$OLD_LIBS"])
if test "$ccc_cv_have_libboost_signals" != yes; then
  CCC_BOOST_NOT_FOUND
fi

CPPFLAGS="$OLD_CPPFLAGS"
LDFLAGS="$OLD_LDFLAGS"

AC_SUBST([BOOST_CPPFLAGS])
AC_SUBST([BOOST_LDFLAGS])

AM_PATH_CPPUNIT(1.8.0)
AM_CONDITIONAL(HAVE_CPPUNIT, test x"$CPPUNIT_LIBS" != x)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT