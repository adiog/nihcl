// ex5-3.c -- Writing a BigInt to the standard output

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex5-3.c,v 3.0 90/05/15 22:45:19 kgorlen Rel $

#include <iostream.h>
#include "BigInt.h"

main()
{
    BigInt b= "1234567890";
    cout << "The BigInt is " << b << endl;
}
