/* $Id$
 *
 * description to follow
 *
 * Copyright (C) 2004 Cryptophon Project <cryptophon@bielefeld.ccc.de>
 * This code is distributed under the GNU General Public License version 2
 */

#ifndef CCCP_DEBUG_H
#define CCCP_DEBUG_H 1

#if HAVE_AUTOSPRINTF

#include <autosprintf.h>

#define BUG(args) do_BUG(__FILE__, __LINE__, gnu::autosprintf args)

#else // !HAVE_AUTOSPRINTF

#define BUG(args) do_BUG(__FILE__, __LINE__)

#endif // !HAVE_AUTOSPRINTF

#define BUG_ON(expr) do { \
        if (expr) \
            do_BUG(__FILE__, __LINE__, #expr); \
    } while (0)

#endif /* !defined(CCCP_DEBUG_H) */

// vim:ft=cpp
