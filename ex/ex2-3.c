// ex2-3.c -- Add instances of class BigInt

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex2-3.c,v 3.0 90/05/15 22:45:05 kgorlen Rel $

#include "BigInt.h"

main()
{
    BigInt a =  "25123654789456";
    BigInt b = "456023398798362";
    BigInt c;
    c = a + b + 47;
    c.print();  printf("\n");
}
