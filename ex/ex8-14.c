// ex8-14.c -- A Dictionary of Patient records keyed by name

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-14.c,v 3.0 90/05/29 14:34:19 kgorlen Rel $

#include "Assoc.h"
#include "Dictionary.h"
#include "Iterator.h"
#include "SortedCltn.h"
#include "String.h"
#include "Patient.h"

main()
{
// Associate key names with Patient records in a Dictionary
    Dictionary dict;
    cout << "Order of Insertion:" << endl;

    String& fried = *new String("Fried Harry I.");
    Patient& patient_fried =
        *new Patient(fried,"987-65-4321",22221);
    dict.addAssoc(fried,patient_fried);
    cout << patient_fried << endl;

    String& smith = *new String("Smith John A.");
    Patient& patient_smith =
        *new Patient(smith,"333-22-1111",22223);
    dict.addAssoc(smith,patient_smith);
    cout << patient_smith << endl;

    String& chavez = *new String("Chavez Maria G.");
    Patient& patient_chavez =
        *new Patient(chavez,"444-555-6666",22223);
    dict.addAssoc(chavez,patient_chavez);
    cout << patient_chavez << endl;
    cout << endl;

// Get sorted list of key Strings
    SortedCltn scltn;
    dict.addKeysTo(scltn);
    
// Print Patient records in sorted order
    cout << "Sorted by Name:" << endl;
    Iterator its(scltn);
    while (its++) {
        cout << *dict.atKey(*its()) << endl;
    }
    cout << endl;

// Process queries
    String name;
    while (YES) {
        cout << "Patient name: "; cin >> name;
        if (cin.eof()) break;
        LookupKey* lk = dict.assocAt(name);
        if (lk) cout << *lk->value() << endl;
        else cout << name << " not found" << endl;
    }
    cout << endl;
}
