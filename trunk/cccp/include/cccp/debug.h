/* $Id$
 *
 * description to follow
 *
 * Copyright (C) 2004 Cryptophon Project <cryptophon@bielefeld.ccc.de>
 * This code is distributed under the GNU General Public License version 2
 */

#ifndef CCCP_DEBUG_H
#define CCCP_DEBUG_H 1

/*! \file
 * A collection of various macros that help in debugging.
 * The macros in this file can only be used inside non-static methods of
 * classes derived from CCCP::Object, since they depend on methods
 * inherited from there to do the grunt work.
 *
 * \todo Replace/extend with a more flexible logging framework.
 */

#if HAVE_AUTOSPRINTF

#include <autosprintf.h>

/*! \defgroup assertions Assertion macros
 */

/*! @{ */

//! Log a bug with file and line number, and abort().
#define BUG(args) do_BUG(__FILE__, __LINE__, gnu::autosprintf args)

#else // !HAVE_AUTOSPRINTF

#define BUG(args) do_BUG(__FILE__, __LINE__)

#endif // !HAVE_AUTOSPRINTF

//! Log bug and abort if \a expr evaluates true.
/*!
 * The same as
 * \code
 * if (expr)
 *     BUG("expr")
 * \endcode
 */
#define BUG_ON(expr) do { \
        if (expr) \
            do_BUG(__FILE__, __LINE__, #expr); \
    } while (0)

#endif /* !defined(CCCP_DEBUG_H) */

/*! @} */

// vim:ft=cpp
