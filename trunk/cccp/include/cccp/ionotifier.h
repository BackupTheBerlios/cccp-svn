/* $Id: ionotifier.h $
 *
 * description to follow
 *
 * Copyright (C) 2004 Cryptophon Project <cryptophon@bielefeld.ccc.de>
 * This code is distributed under the GNU General Public License version 2
 */

#ifndef CCCP_IONOTIFIER_H
#define CCCP_IONOTIFIER_H 1

#include <cccp/object.h>

namespace CCCP {

struct IONotifierPrivate;

class IONotifier : public Object {
public:
    enum Type {
        Read,
        Write
    };

    IONotifier(int fd, Type type, Object* parent = 0, const char* name = 0);
    virtual ~IONotifier();

    int fd() const;
    Type type() const;

    boost::signal<void (IONotifier*, int)> activated;

private:
    IONotifierPrivate* d;
}; // class IONotifier

}; // namespace CCCP

#endif /* !defined(CCCP_IONOTIFIER_H) */

// vim:ft=cpp
