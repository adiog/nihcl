// ex8-9.c -- Sorting on Multiple Keys with ArrayOb and KeySortCltn

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-9.c,v 3.0 90/05/15 22:46:30 kgorlen Rel $

#include "KeySortCltn.h"
#include "ArrayOb.h"
#include "Assoc.h"
#include "Patient.h"
#include "Integer.h"

void sort_Patient(KeySortCltn& c, Patient& p)
{
// Set up ArrayOb with sort keys zip,name,ss_number
    ArrayOb& key = *new ArrayOb(3);
    key[0] = new Integer(p.zip());
    key[1] = new String(p.name());
    key[2] = new String(p.ssn());
    c.addAssoc(key,p);
}

main()
{
    KeySortCltn cltn;

// Define 6 Patient records 
// in parent/child pairs with the same name and zip
// and sort with ArrayOb key in a KeySortCltn
    sort_Patient(cltn,
        *new Patient("Smith John A.","333-22-1111",22223));
    sort_Patient(cltn,
        *new Patient("Smith John A.","111-22-3333",22223));
    sort_Patient(cltn,
        *new Patient("Fried Harry I.","987-65-4321",22221));
    sort_Patient(cltn,
        *new Patient("Fried Harry I.","123-45-6789",22221));
    sort_Patient(cltn,
        *new Patient("Chavez Maria G.","666-555-4444",22223));
    sort_Patient(cltn,
        *new Patient("Chavez Maria G.","444-555-6666",22223));

// Print Patient records in sorted order
    cout << "Sort by zip, name, and ssn: \n\n";

    Iterator it(cltn);
    while (it++) {
        Assoc& as = *(Assoc*)it();
        cout << *as.value() << endl;
    }
}
