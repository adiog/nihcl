// ex8-4.c -- Incorrectly modifying a container during iteration

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-4.c,v 3.0 90/05/15 22:46:19 kgorlen Rel $

#include "OrderedCltn.h"
#include "Iterator.h"
#include "String.h"

main()
{
    OrderedCltn symbols;
    symbols.add(*new String("A"));
    symbols.add(*new String("C"));
    symbols.add(*new String("G"));
    symbols.add(*new String("T"));

    Iterator it(symbols);
    while (it++)
        if (it()->compare(String("G")) < 0) symbols.remove(*it());

    cout << symbols << endl;
}
