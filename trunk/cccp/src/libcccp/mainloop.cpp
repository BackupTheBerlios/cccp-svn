/* $Id: mainloop.cpp $
 *
 * description to follow
 *
 * Copyright (C) 2004 Cryptophon Project <cryptophon@bielefeld.ccc.de>
 * This code is distributed under the GNU General Public License version 2
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <list>
#include <map>

#include <cassert>

#include <cccp/ionotifier.h>
#include <cccp/mainloop.h>

namespace CCCP {

struct IONotifierPrivate {
    MainLoop* ml;
    int fd;
    IONotifier::Type type;
};

IONotifier::IONotifier(int fd, IONotifier::Type type, Object* parent, const char* name)
    : Object(parent, name)
{
    d = new IONotifierPrivate;

    d->ml = theMainLoop;
    d->fd = fd;
    d->type = type;

    d->ml->addNotifier(this);
}

IONotifier::~IONotifier()
{
    d->ml->removeNotifier(this);
    delete d;
}

int
IONotifier::fd() const
{
    return d->fd;
}

IONotifier::Type
IONotifier::type() const
{
    return d->type;
}

struct MainLoopPrivate {
    typedef std::map<int, std::list<IONotifier*> > IONFdMap;

    IONFdMap notif;

    fd_set read_set, write_set, except_set;
    int maxfd;
}; // class MainLoopPrivate

MainLoop::MainLoop(Object* parent, const char* name)
    : Object(parent, name)
{
    d = new MainLoopPrivate;

    FD_ZERO(&d->read_set);
    FD_ZERO(&d->write_set);
    FD_ZERO(&d->except_set);
    d->maxfd = -1;
}

MainLoop::~MainLoop()
{
    delete d;
}

void
MainLoop::run()
{
    // FIXME
}

void
MainLoop::iteration()
{
    // FIXME
}

void
MainLoop::quit()
{
    // FIXME
}

void
MainLoop::quitNow()
{
    // FIXME
}

void
MainLoop::addNotifier(IONotifier* ion)
{
    d->notif[ion->fd()].push_back(ion);

    switch (ion->type()) {
    case IONotifier::Read:
        FD_SET(ion->fd(), &d->read_set);
        break;

    case IONotifier::Write:
        FD_SET(ion->fd(), &d->write_set);
        break;
    }

    // we always look for exceptions
    FD_SET(ion->fd(), &d->except_set);

    if (ion->fd() >= d->maxfd)
        d->maxfd = ion->fd()+1;
}

void
MainLoop::removeNotifier(IONotifier* ion)
{
    MainLoopPrivate::IONFdMap::iterator it;
    it = d->notif.find(ion->fd());
    if (it != d->notif.end()) {
    }
}

MainLoop* theMainLoop;

}; // namespace CCCP
