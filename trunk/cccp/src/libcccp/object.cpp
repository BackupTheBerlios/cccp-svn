/* $Id$
 *
 * description to follow
 *
 * Copyright (C) 2004 Cryptophon Project <cryptophon@bielefeld.ccc.de>
 * This code is distributed under the GNU General Public License version 2
 */

// uncomment to get debug message about CCC::Object {con,de}struction
//#define DEBUG_OBJECT 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifndef DEBUG_OBJECT
#undef NDEBUG
#define NDEBUG 1
#endif

#include <vector>
#include <algorithm>
#include <boost/bind.hpp>
#include <cccp/object.h>

#ifdef DEBUG_OBJECT
#include <iostream>
#endif

#include <cassert>

namespace CCCP {

Object::Object(Object* parent, const char* name)
    : boost::signals::trackable(),
      m_name(name),
      m_parent(0),
      m_children(),
      m_destroying(false)
{
#ifdef DEBUG_OBJECT
    std::cerr << "Initializing \"" << (m_name?m_name:"unnamed") << "\"" << std::endl;
#endif

    reparent(parent);
}

Object::~Object()
{
#ifdef DEBUG_OBJECT
    std::cerr << "Destroying \"" << (m_name?m_name:"unnamed") << "\"..." << std::endl;
#endif

    // delete children first
    m_destroying = true;
    std::vector<Object*>::iterator i;
    for (i = m_children.begin(); i != m_children.end(); i++)
        delete *i;

    if (m_parent != 0)
        m_parent->removeChild(this);

    // emit destroyed() signal
    destroyed(this);

#ifdef DEBUG_OBJECT
    std::cerr << "... finished destroying \"" << (m_name?m_name:"unnamed") << "\"" << std::endl;
#endif
}

/*!
 * Changes the parent of an object, and thus the position of the object
 * in the global object hierarchy.  Passing a null pointer as the
 * argument makes the object a root object, ie. an object that has no
 * parent.
 *
 * Reparenting results in the emission of the childRemoved() signal from
 * the old parent (if the object isn't a root object) and the
 * childAdded() signal from the new parent (if non-null), in this order.
 *
 * \param parent The new parent that the object should become a child
 *               of (may be null).
 *
 * \internal reparent() is also used by the constructor to initially set
 * the parent at object construction time.  This also results in a
 * childAdded() signal (but no childRemoved(), since there is no
 * previous parent).
 */
void
Object::reparent(Object* parent)
{
    if (m_parent != 0)
        m_parent->removeChild(this);
    m_parent = parent;
    if (parent != 0)
        parent->addChild(this);
}

void
Object::addChild(Object* child)
{
    assert(child != 0);
    assert(std::find(m_children.begin(),
                     m_children.end(),
                     child) == m_children.end());

    m_children.push_back(child);
    childAdded(this, child);
}

void
Object::removeChild(Object* child)
{
    assert(child != 0);
    if (!m_destroying) {
        std::vector<Object*>::iterator pos(std::find(m_children.begin(),
                                                     m_children.end(),
                                                     child));
        assert(pos != m_children.end());
        m_children.erase(pos);
    }
    childRemoved(this, child);
}

}; // namespace CCCP
