// ex5-4.c -- Extending stream I/O for class BigInt

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex5-4.c,v 3.0 90/05/29 14:34:12 kgorlen Rel $

#include "BigInt.h"
#include <osfcn.h>

main()
{
    BigInt a,b;
    while ( cin.good() ) {
        cout << "Enter a: "; cin >> a;
        if (cin.fail()) break;
        cout << "Enter b: "; cin >> b;
        if (cin.fail()) break;
        cout << "a+b=" << (a+b) << endl;
    }
    cout << endl;
}
