// ex8-3.c -- Nested Iterators

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-3.c,v 3.0 90/05/15 22:46:16 kgorlen Rel $

#include "OrderedCltn.h"
#include "Iterator.h"
#include "String.h"

void printPairs(const Collection& c1, const Collection& c2)
{
    Iterator it1(c1), it2(c2);

    while(it1++) {
        while (it2++) {
            cout << '[' << *it1() << ',' << *it2() << "]  ";
        }
        cout << endl;
        it2.reset();
    }
}

main()
{
    OrderedCltn symbols;
    symbols.add(*new String("A"));
    symbols.add(*new String("C"));
    symbols.add(*new String("G"));
    symbols.add(*new String("T"));
    printPairs(symbols,symbols);
}
