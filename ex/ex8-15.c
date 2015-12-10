// ex8-15.c -- Comparison of classes Dictionary and IdentDict

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-15.c,v 3.0 90/05/15 22:46:11 kgorlen Rel $

#include "Dictionary.h"
#include "IdentDict.h"
#include "LookupKey.h"
#include "String.h"
#include "SortedCltn.h"

main()
{
    String s1 = "A String";

    Dictionary d;
    d.addAssoc(s1,*new String("value associated with s1"));
    cout << "Dictionary:" << endl;
    LookupKey* lk = d.assocAt(String("A String"));
    if (lk) cout << *lk->value() << endl;
    else cout << "Not found" << endl;
    lk = d.assocAt(s1);
    if (lk) cout << *lk->value() << endl;
    else cout << "Not found" << endl;
    cout << endl;

    IdentDict i;
    i.addAssoc(s1,*new String("value associated with s1"));
    cout << "IdentDict:" << endl;
    lk = i.assocAt(String("A String"));
    if (lk) cout << *lk->value() << endl;
    else cout << "Not found" << endl;
    lk = i.assocAt(s1);
    if (lk) cout << *lk->value() << endl;
    else cout << "Not found" << endl;
}
