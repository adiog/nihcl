// ex6-3.c -- Order of construction of base and member classes

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex6-3.c,v 3.0 90/05/15 22:45:44 kgorlen Rel $

#include <iostream.h>

class X {
    int i;
public:
    X(const char* s)    { cout << s << ' '; }
    X()                 { cout << "X::X() "; }
};

class A {
    X a1;
    X a2;
public:
    A(const char* s): a2("A::a2") { cout << s << ' '; }
};

class B: public A {
    X b1;
    X b2;
public:
    B(const char* s):
        b2("B::b2"),
        b1("B::b1"),
        A("B::A")   { cout << s << ' '; }
};

int initCi()
{
    cout << "C::i ";
    return 0;
}

int& initCr()
{
    static int n = 1;
    cout << "C::r ";
    return n;
}

class C: public B {
    const int i;
    int& r;
    X c1;
    X c2;
public:
    C(const char* s):
        B("C::B"),
        c1("C::c1"),
        r(initCr()),
        i(initCi()),
        c2("C::c2") { cout << s << endl; }
};

main()
{
    C c("c");
}
