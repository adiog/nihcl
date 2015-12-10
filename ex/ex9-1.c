// ex9-1.c -- Class ArrayOb example

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex9-1.c,v 3.0 90/05/15 22:46:32 kgorlen Rel $

#include "ArrayOb.h"
#include "Point.h"
#include "String.h"
#include "Date.h"

main()
{
    ArrayOb a(3),b(3);          // two ArrayObs with size 3
    cout << "The size of a is " << a.size() << endl;
    a[0] = new Point(0,0);      // 0-origin indexing, like C
    a[1] = new Date(10,"March",1986);
    a[2] = new String("hello");
    cout << *a[2] << endl;
    b = a;
    if (a == b) cout << "a equals b, as it should\n";
    b[2] = new String("goodbye");
    if (a != b) cout << "a does not equal b any more\n";
    cout << b << endl;
}
