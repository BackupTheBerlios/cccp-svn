/* $Id$
 *
 * description to follow
 *
 * Copyright (C) 2004 Cryptophon Project <cryptophon@bielefeld.ccc.de>
 * This code is distributed under the GNU General Public License version 2
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <cccp/object.h>

int
main(void)
{
    CCCP::Object a(0, "a"), b(0, "b");
    CCCP::Object* parent = new CCCP::Object(0, "parent");
    CCCP::Object* child1 = new CCCP::Object(parent, "child 1");
    new CCCP::Object(child1, "grandchild 1");
    new CCCP::Object(child1, "grandchild 1");
    CCCP::Object* child2 = new CCCP::Object(parent, "child 2");

    delete parent;

    return 0;
}
