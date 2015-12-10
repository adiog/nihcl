// ex5-2.c -- Reading from the standard input

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex5-2.c,v 3.0 90/05/15 22:45:16 kgorlen Rel $

#include <iostream.h>

main()
{
    float x;
    int i;
    char* prompt = "Enter [float int]?";

    cout << prompt << flush;
    cin >> x >> i;

    cout << "x=" << x << " i=" << i << endl;
}
