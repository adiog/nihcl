// ex8-6.c -- Sequential access to Objects in an OrderedCltn

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-6.c,v 3.0 90/05/15 22:46:22 kgorlen Rel $

#include "OrderedCltn.h"
#include "Iterator.h"
#include "Patient.h"

main()
{
// new Patient objects to put in OrderedCltn
    Patient* p1 =new Patient("Smith John A.","111-22-3333",22222);
    Patient* p2 =new Patient("Fried Harry I.","123-45-6789",22221);
    Patient* p3 =
      new Patient("Chavez Maria G.","444-555-6666",22223);

// add each Patient to OrderedCltn
    OrderedCltn patientlist(1);// capacity=1 (default=16)
    patientlist.add(*p1);      // at[0] in order
    patientlist.add(*p2);      // at[1] in order
    patientlist.add(*p3);      // at[2] in order

    cout << "ACCESS OBJECTS WITH operator[]():" << endl;
    for(int i=0; i<patientlist.size(); i++) {
        Patient& p = *(Patient*)patientlist[i];
        cout << p << endl;
    }

    cout << "ACCESS OBJECTS WITH Iterator:" << endl;
    Iterator it(patientlist);
    while ( it++ ) {
        Patient& p = *(Patient*)it();
        cout << p << endl;
    }
}
