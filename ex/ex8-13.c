// ex8-13.c -- Comparison of classes Set and IdentSet

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-13.c,v 3.0 90/05/15 22:46:06 kgorlen Rel $

#include "Set.h"
#include "IdentSet.h"
#include "String.h"
#include "SortedCltn.h"

main()
{
    String s1 = "A String";
    String s2 = "A String";
    String s3 = "Another String";

    Set s;
    s.add(s1); s.add(s2); s.add(s3); s.add(s3);
    cout << "Set:\n";
    cout << s.asSortedCltn() << endl;

    IdentSet i;
    i.add(s1); i.add(s2); i.add(s3); i.add(s3);
    cout << "\nIdentSet:\n";
    cout << i.asSortedCltn() << endl;
}
