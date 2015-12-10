// ex9-3.c -- Correct handling of member pointers
//            to class instances

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex9-3.c,v 3.0 90/05/15 22:46:36 kgorlen Rel $

#include "String.h"

class X {
    String* s;
public:
    X(const char* t="")     { s = new String(t); }
    X(const X& x)           { s = new String(*x.s); }
    void operator=(const X&);
    ~X()                    { delete s; }
    void set(const char* t) { *s = t; }
    friend ostream& operator<<(ostream& strm, X& x) {
        strm << *x.s;
        return strm;
    }
};

void X::operator=(const X& x)
{
    if (this == &x) return;
    delete s;
    s = new String(*x.s);
}

main()
{
    X a = "abc";
    X b = a;
    X c;
    c = a;
    a.set("xyz");
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "c=" << c << endl;
}
