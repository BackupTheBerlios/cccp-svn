/* $Id: object.cpp $
 *
 * description to follow
 *
 * Copyright (C) 2004 Cryptophon Project <cryptophon@bielefeld.ccc.de>
 * This code is distributed under the GNU General Public License version 2
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <boost/bind.hpp>

#include <cccp/object.h>

namespace CCCPTest {

namespace {

class DestructionTester : public CCCP::Object {
public:
    DestructionTester(bool& flag, CCCP::Object* parent, const char* name)
        : CCCP::Object(parent, name), m_flag(flag)
    {
    }

    virtual ~DestructionTester()
    {
        m_flag = true;
    }

private:
    bool& m_flag;
}; // class DestructionTester

class SingleArgSignalHelper {
public:
    int& called;
    CCCP::Object*& sigArg;
    SingleArgSignalHelper(int& c, CCCP::Object*& sa)
        : called(c), sigArg(sa) { }
    void operator() (CCCP::Object* arg) { called++; sigArg = arg; }
}; // SingleArgSignalHelper

class TwoArgSignalHelper {
public:
    int& called;
    CCCP::Object*& sigArg1;
    CCCP::Object*& sigArg2;
    TwoArgSignalHelper(int& c, CCCP::Object*& sa1, CCCP::Object*& sa2)
        : called(c), sigArg1(sa1), sigArg2(sa2) { }
    void operator() (CCCP::Object* arg1, CCCP::Object* arg2)
        { called++; sigArg1 = arg1; sigArg2 = arg2; }
}; // class TwoArgSignalHelper

}; // anon namespace

class ObjectTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ObjectTest);
    CPPUNIT_TEST(destroyedSignal);
    CPPUNIT_TEST(childDestruction);
    CPPUNIT_TEST(grandchildDestruction);
    CPPUNIT_TEST(childAddedSignal);
    CPPUNIT_TEST_SUITE_END();

private:
    CCCP::Object* root;

public:
    void setUp()
    {
        root = new CCCP::Object(0, "CCCPTest::ObjectTest root object");
    }

    void tearDown()
    {
        delete root;
    }

    void destroyedSignal()
    {
        int called = 0;
        CCCP::Object* sigArg = 0;

        CCCP::Object* obj = new CCCP::Object(root, "test object");
        obj->destroyed.connect(SingleArgSignalHelper(called, sigArg));
        delete obj;

        CPPUNIT_ASSERT(called == 1);
        CPPUNIT_ASSERT(sigArg == obj);
    }

    void childDestruction()
    {
        bool destroyedChild = false;
        new DestructionTester(destroyedChild, root, "DestructionTester");
        delete root;
        root = 0;
        CPPUNIT_ASSERT(destroyedChild == true);
    }

    void grandchildDestruction()
    {
        bool destroyedGrandchild = false;
        CCCP::Object* child = new CCCP::Object(root, "child object");
        new DestructionTester(destroyedGrandchild, child, "DestructionTester");
        delete root;
        root = 0;
        CPPUNIT_ASSERT(destroyedGrandchild = true);
    }

    void childAddedSignal()
    {
        int called = 0;
        CCCP::Object* sigArg1 = 0;
        CCCP::Object* sigArg2 = 0;

        root->childAdded.connect(TwoArgSignalHelper(called, sigArg1, sigArg2));

        CCCP::Object* obj = new CCCP::Object(root, "child object");

        CPPUNIT_ASSERT(called == 1);
        CPPUNIT_ASSERT(sigArg1 == root);
        CPPUNIT_ASSERT(sigArg2 == obj);
    }
}; // class ObjectTest

CPPUNIT_TEST_SUITE_REGISTRATION(ObjectTest);

}; // namespace CCCPTest
