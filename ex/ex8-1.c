// ex8-1.c -- Description of a Patient object

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-1.c,v 3.0 90/05/15 22:45:53 kgorlen Rel $

#include "Patient.h"

main()
{
    Patient aPatient("Doe, John","000-00-0000",12345);

    cout << "Class[" << aPatient.className() << "] "
         << "ByteSize[" << sizeof(aPatient) << "]" << endl;
    aPatient.dumpOn(cout);
}
