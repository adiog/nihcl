// ex13-7.c -- Calling a virtual function from a
//             base class constructor

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex13-7.c,v 3.0 90/05/15 22:44:47 kgorlen Rel $

#include <iostream.h>

class V {
public:
    virtual void vf();
};

void V::vf()    { cout << "V::vf()" << endl; }

class A: public virtual V {
public:
    A()         { /* ... */ }
    virtual void vf();
};

void A::vf()    { cout << "A::vf()" << endl; }

class B: public virtual V {
public:
    B()         { vf(); }   // Calls A::vf(), not
                            // V::vf() or C::vf()
};

class C: public A, public B {
public:
    C()         { vf(); }   // Calls C::vf()
    virtual void vf();
};

void C::vf()    { cout << "C::vf()" << endl; }

main()
{
    C c;
}
