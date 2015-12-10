// ex5-9 -- matrix algebra with Class Matrix

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex5-9.c,v 3.0 90/05/15 22:45:37 kgorlen Rel $

#include <iostream.h>
#include "Matrix.h"

    double c_1[] = { 1.1, 2.1, 3.1 };
    double c_2[] = { 1.2, 2.2, 3.2 };
    double c_3[] = { 1.3, 2.3, 3.3 };

main()
{
    // construct columns and concatenate
    Matrix c1(3, 1, c_1);
    Matrix c2(3, 1, c_2);
    Matrix c3(3, 1, c_3);
    Matrix m = c1&c2&c3;   // concatenate columns

    cout << m << endl;

    // extract row vector
    Matrix v = m.row(1);
    cout << v << endl;

    // multiply matrix by column matrix
    Matrix u = m*v.t();
    cout << u << endl;
}
