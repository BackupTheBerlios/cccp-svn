/* $Id$
 *
 * description to follow
 *
 * Copyright (C) 2004 Cryptophon Project <cryptophon@bielefeld.ccc.de>
 * This code is distributed under the GNU General Public License version 2
 */

#ifndef CCCP_OBJECT_H
#define CCCP_OBJECT_H 1

#include <vector>
#include <boost/signal.hpp>
#include <boost/signals/trackable.hpp>

namespace CCCP {

//! Abstract base class for the inheritance tree.
/*!
 * It provides some basic capabilities to all classes that inherit
 * (either directly or indirectly) from CCC::Object:
 *
 * \li Organization of objects into an object hierarchy.  When an object
 *     is destroyed, all child objects (and grandchilds etc.) are
 *     automatically freed, too.  This helps to avoid ressource leaks.
 * \li Objects are "trackable", ie. any signals that are connected to
 *     the object are automatically disconnected when the object is
 *     destroyed (see documentation of the Boost.Signals library for
 *     detailed information).
 * \li Provide some generic signals that are emitted when an object is
 *     being destroyed or changes in the object hierarchy occur.
 *
 * \todo Provide methods for output of debug messages that automatically
 *       include the name of the object.
 */
class Object : public boost::signals::trackable {
public:
    //! Default constructor.
    Object(Object* parent = 0, const char* name = 0);
    //! Class hierarchies almost always need a virtual destructor.
    virtual ~Object();

    //! Change the place of an object in the object hierarchy.
    void reparent(Object* parent);

    Object* parent() const { return m_parent; }

    //! The object is being destroyed.
    /*!
     * The argument is the object that is being destroyed.
     */
    boost::signal<void (Object*)> destroyed;

    //! Signal addition of a new child object.
    /*!
     * The first argument is the object that the new child is being
     * added to.  The second argument is the new child object itself.
     *
     * At the time the signal is emitted the object has already been
     * added as a child to its new parent.
     */
    boost::signal<void (Object*, Object*)> childAdded;
    //! Signal removal of a child object.
    /*!
     * The first argument is the object that the child has been removed
     * from.  The second argument is the removed child object itself.
     *
     * At the time the signal is emitted the object has already been
     * removed from its parent child list.
     */
    boost::signal<void (Object*, Object*)> childRemoved;

    const std::vector<Object*>& children() const { return m_children; }

private:
    //! Add a new child object to the object.
    void addChild(Object* child);
    //! Remove a child object.
    void removeChild(Object* child);

private:
    const char* m_name;
    Object* m_parent;
    std::vector<Object*> m_children;
    bool m_destroying;

protected:
    void do_BUG(const char* file, int line, const char* msg = 0);
}; // class Object

}; // namespace CCCP

#endif /* !defined(CCCP_OBJECT_H) */

// vim:ft=cpp
