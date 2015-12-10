// ex8-2.c -- Use of an Iterator with container
//            for objects of unknown class

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-2.c,v 3.0 90/05/15 22:46:14 kgorlen Rel $

#include "OrderedCltn.h"
#include "Iterator.h"
#include "String.h"

void listContainer(ostream& strm,Collection& cltn)
{
//  Iterator knows neither
//  the actual class of cltn nor    
//  the actual class of any Object in cltn
    Iterator it(cltn);    
    while (it++) strm << *it() << " ";    
}

main()
{
    OrderedCltn symbols;
    symbols.add(*new String("A"));
    symbols.add(*new String("C"));
    symbols.add(*new String("G"));
    symbols.add(*new String("T"));

    listContainer(cout,symbols);
    cout << endl;
}
