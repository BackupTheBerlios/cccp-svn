## Process Makefile.am with automake to create Makefile.in. -*- Makefile -*-
## Written by Andreas Ferber <sunshine@bielefeld.ccc.de>

nobase_include_HEADERS = \
	cccp/object.h		\
	cccp/mainloop.h		\
	cccp/ionotifier.h	\
	cccp/debug.h

uninstall-hook:
	-rmdir $(DESTDIR)$(includedir)/cccp

MAINTAINERCLEANFILES = \
	config.h.in

# vim:ft=make
