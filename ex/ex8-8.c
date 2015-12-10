// ex8-8.c -- sorting Patient records with a KeySortCltn

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-8.c,v 3.0 90/05/15 22:46:26 kgorlen Rel $

#include "Assoc.h"
#include "Integer.h"
#include "Iterator.h"
#include "KeySortCltn.h"
#include "String.h"
#include "Patient.h"

main()
{
// Build list of Patient records
    OrderedCltn cltn;
    cltn.add(*new Patient("Smith John A.","111-22-3333",22222));
    cltn.add(*new Patient("Fried Harry I.","123-45-6789",22221));
    cltn.add(*new Patient("Chavez Maria G.","444-555-6666",22223));

// Three KeySortCltn collections for three different keys
    KeySortCltn sort0(cltn.size());
    KeySortCltn sort1(cltn.size());
    KeySortCltn sort2(cltn.size());

    Iterator it(cltn);
    while ( it++ )  {
        Patient& p = *(Patient*)it();
    
// Sort Patient by name
        sort0.addAssoc(*new String(p.name()),p);

// Sort Patient by social security number
        sort1.addAssoc(*new String(p.ssn()),p);

// Sort Patient by zip code
        sort2.addAssoc(*new Integer(p.zip()),p);
    }

    cout << "SORT BY NAME:\n"
         << sort0 << '\n' << endl;

    cout << "SORT BY SOCIAL SECURITY NUMBER:\n"
         << sort1 << '\n' << endl;

    cout << "SORT BY ZIP CODE:\n"
         << sort2 << '\n';
}
