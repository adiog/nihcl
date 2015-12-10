// ex8-7.c -- sorting Patient records by name

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-7.c,v 3.0 90/05/15 22:46:24 kgorlen Rel $

#include "SortedCltn.h"
#include "String.h"
#include "Patient.h"

main()
{
    SortedCltn cltn;
    cltn.add(*new Patient("Smith John A.","111-22-3333",22222));
    cltn.add(*new Patient("Fried Harry I.","123-45-6789",22221));
    cltn.add(*new Patient("Chavez Maria G.","444-555-6666",22223));

    cout << cltn << endl;
}
