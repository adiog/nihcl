// ex8-5.c -- Modifying a container during iteration

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-5.c,v 3.0 90/05/15 22:46:20 kgorlen Rel $

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

    OrderedCltn temp = symbols;
    Iterator it(temp);
    while (it++)
        if (it()->compare(String("G")) < 0)
            symbols.removeId(*it());

    cout << symbols << endl;
}
