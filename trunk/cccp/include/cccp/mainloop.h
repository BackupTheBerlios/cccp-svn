/* $Id$
 *
 * description to follow
 *
 * Copyright (C) 2004 Cryptophon Project <cryptophon@bielefeld.ccc.de>
 * This code is distributed under the GNU General Public License version 2
 */

#ifndef CCCP_MAINLOOP_H
#define CCCP_MAINLOOP_H 1

#include <cccp/ionotifier.h>
#include <cccp/object.h>

namespace CCCP {

class IONotifier;
struct MainLoopPrivate;

class MainLoop : public Object {
public:
    MainLoop(Object* parent = 0, const char* name = 0);
    virtual ~MainLoop();

    virtual void run();

    virtual void iteration();

    // quit mainloop when control returns from the current call chain
    void quit();
    // quit mainloop immediately, aborting the current call chain
    void quitNow();

private:
    void addNotifier(IONotifier* ion);
    void removeNotifier(IONotifier* ion);

    MainLoopPrivate* d;

    friend class IONotifier;
}; // class MainLoop

extern MainLoop* theMainLoop;

}; // namespace CCCP

#endif /* !defined(CCCP_MAINLOOP_H) */

// vim:ft=cpp
