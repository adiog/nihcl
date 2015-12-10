// ex5-1.c -- Writing to the standard output stream

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex5-1.c,v 3.0 90/05/15 22:45:07 kgorlen Rel $

#include <iostream.h>

main()
{
    float x = 1.2;
    int i = 3;
    char* prog = "myprogram";

    cout << prog;
    cout << ":";
    cout << endl;

    cout << "at step " << i << ", x = " << x << endl;
}
