// ex13-5.c -- Virtual base classes and virtual functions

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex13-5.c,v 3.0 90/05/15 22:44:43 kgorlen Rel $

#include <iostream.h>

class V {
public:
    virtual void vf();
};

void V::vf()    { cout << "V::vf()" << endl; }

class A: public virtual V {
public:
    virtual void vf();
};

void A::vf()    { cout << "A::vf()" << endl; }

class B: public virtual V {
public:
    void fb()   { vf(); }
};

class C: public A, public B {
};

class D: public A, public B {
public:
    virtual void vf();
};

void D::vf()    { cout << "D::vf()" << endl; }

main()
{
    B b;
    b.fb();  // B::fb() calls V::vf()
    C c;
    c.fb();  // B::fb() calls A::vf() -- on another path of the DAG
    D d;
    d.fb();  // B::fb() calls D::vf()
}
