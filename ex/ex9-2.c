// ex9-2.c -- Incorrect handling of member
//            pointers to class instances

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex9-2.c,v 3.0 90/05/15 22:46:35 kgorlen Rel $

#include "String.h"

class X {
    String* s;
public:
    X(const char* t="")     { s = new String(t); }
    ~X()                    { delete s; }
    void set(const char* t) { *s = t; }
    friend ostream& operator<<(ostream& strm, X& x) {
        strm << *x.s;
        return strm;
    }
};

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
