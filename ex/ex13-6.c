// ex13-6.c -- Order of construction of multiple base,
//             virtual base, and member classes

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex13-6.c,v 3.0 90/05/15 22:44:45 kgorlen Rel $

#include <iostream.h>

class X {
public:
    X(const char* s)    { cout << s << ' '; }
    X()                 { cout << "X::X() "; }
};

class V: public X {
public:
    V(const char* s = "default"):
        X("V::X")       { cout << s << ' '; }
};

class A {
    X a1;
    X a2;
public:
    A(const char* s): a2("A::a2") { cout << s << ' '; }
};

class B1: public A, public virtual V {
    X b1;
    X b2;
public:
    B1(const char* s):
        b2("B1::b2"),
        b1("B1::b1"),
        V("B1::V"),
        A("B1::A")      { cout << s << ' '; }
};

class B2: public virtual V, public A {
    X b1;
    X b2;
public:
    B2(const char* s):
        b1("B2::b1"),
        b2("B2::b2"),
        A("B2::A"),
        V("B2::V")      { cout << s << ' '; }
};

class C: public B1, public B2 {
    int i;
    X c1;
    X c2;
public:
    C(const char* s):
        B2("C::B2"),
        c1("C::c1"),
        i((cout << "C::i ",0)),
        B1("C::B1"),
        V("C::V"),
        c2("C::c2")     { cout << s << endl; }
};

main()
{
    C c("c");
}
