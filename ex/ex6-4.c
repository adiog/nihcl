// ex6-4.c -- Calling a virtual function from a
//            base class constructor

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex6-4.c,v 3.0 90/05/15 22:45:46 kgorlen Rel $

#include <iostream.h>

class A {
public:
    virtual void vf();
};

void A::vf()    { cout << "A::vf()" << endl; }

class B: public A {
public:
    B()         { vf(); }   // Calls A::vf(), not C::vf()
};

class C: public B {
public:
    C()         { vf(); }   // Calls C::vf()
    virtual void vf();
};

void C::vf()    { cout << "B::vf()" << endl; }

main()
{
    C c;
}
