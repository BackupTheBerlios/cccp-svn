dnl $Id$ -*- shell-script -*-
dnl
dnl description to follow
dnl
dnl Copyright (C) 2004 Andreas Ferber <sunshine@bielefeld.ccc.de>
dnl This code is distributed under the GNU General Public License version 2

AC_DEFUN([CCCP_INIT_DOXYGEN],
[
AC_PATH_PROG([DOT], [dot], [])
AC_SUBST([DOT])
if test -n "$DOT"; then
  CCCP_HAVE_DOT="YES"
else
  CCCP_HAVE_DOT="NO"
fi
AC_SUBST([CCCP_HAVE_DOT])
AC_PATH_PROG([DOXYGEN], [doxygen], [])
AC_SUBST([DOXYGEN])

DOXYGEN_PROJECT_NAME="$1"
DOXYGEN_PROJECT_NUMBER="$2"
AC_SUBST([DOXYGEN_PROJECT_NAME])
AC_SUBST([DOXYGEN_PROJECT_NUMBER])

CCCP_HAS_DOXYGEN=no
if test -n "$DOXYGEN" && test -x "$DOXYGEN"; then
  CCCP_HAS_DOXYGEN=yes
fi
AC_SUBST([CCCP_HAS_DOXYGEN])
])

dnl vi:ts=8 sw=2
dnl vim:ft=autoconf
