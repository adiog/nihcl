// ex13-3.c -- Virtual functions and multiple inheritance

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex13-3.c,v 3.0 90/05/15 22:44:39 kgorlen Rel $

#include <iostream.h>

class A {
public:
    virtual void f()    { cout << "A::f()" << endl; }
};

class B {
public:
    virtual void f()    { cout << "B::f()" << endl; }
};

class C: public A, public B {
public:
    virtual void f()    { cout << "C::f()" << endl; }
};

main()
{
    A* pa = new C;
    B* pb = new C;
    C* pc = new C;
    pa->f();        // calls C::f()
    pb->f();        // calls C::f()
    pc->f();        // calls C::f()
}
