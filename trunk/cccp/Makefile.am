## Process Makefile.am with automake to create Makefile.in. -*- Makefile -*-
## Written by Andreas Ferber <sunshine@bielefeld.ccc.de>

AUTOMAKE_OPTIONS = 1.7

SUBDIRS = include src tests

ACLOCAL_AMFLAGS = -I m4

MAINTAINERCLEANFILES = \
	configure 		\
	aclocal.m4		\
	admin/config.guess 	\
	admin/config.sub	\
	admin/depcomp		\
	admin/install-sh	\
	admin/missing		\
	admin/mkinstalldirs

maintainer-clean-local:
	-find -name Makefile.in | xargs rm -f

# vim:ft=make
