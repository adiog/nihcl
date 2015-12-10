// ex8-12.c -- Binary Set operators

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-12.c,v 3.0 90/05/15 22:46:03 kgorlen Rel $

#include "Patient.h"
#include "Set.h"
#include "SortedCltn.h"

main()
{
    Patient p1("Smith John A.","111-22-3333",22222);
    Patient p2("Fried Harry I.","123-45-6789",20892);
    Patient p3("Chavez Maria G.","444-555-6666",22223);
    Patient p4("Doe, Jane B.","123-98-7654",20892);

    Set males;                  // set of all male Patients
    males.add(p1); males.add(p2);
    Set females;                // set of all female Patients
    females.add(p3); females.add(p4);
    Set washingtonResidents;    // set of all Patients living
                                // in Washington
    washingtonResidents.add(p2); washingtonResidents.add(p4);

    cout << "All patients:\n";
    cout << (males | females).asSortedCltn() << endl;

    cout << "\nAll female patients living in Washington:\n";
    cout << (females & washingtonResidents).asSortedCltn() << endl;

    cout <<
      "\nAll female patients living outside of Washington:\n";
    cout << (females - washingtonResidents).asSortedCltn() << endl;

    cout << "\nDo all male patients live in Washington? "; 
    cout << (males == (males & washingtonResidents) ? "Yes" : "No")
        << endl;
}
