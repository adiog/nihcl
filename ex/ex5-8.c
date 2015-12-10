// ex5-8.c -- Vector operations

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex5-8.c,v 3.0 90/05/15 22:45:35 kgorlen Rel $

#include "IntVec.h"

static int initV[] = {1,2,3,4,5,6,7,8};
static int initW[] = {8,7,6,5,4,3,2,1};
static int initI[] = {1,3,7,2};
static int initJ[] = {-1,-2,-3,-4};

main()
{
    IntVec V(initV,sizeof(initV)/sizeof(int));
                                // V = 1 2 3 4 5 6 7 8
    IntVec W(initW,sizeof(initW)/sizeof(int));
                                // W = 8 7 6 5 4 3 2 1
    IntVec I(initI,sizeof(initI)/sizeof(int));  // I = 1 3 7 2
    IntVec J(initJ,sizeof(initJ)/sizeof(int));  // J = -1 -2 -3 -4
    cout << -V << endl;         // prints -1 -2 -3 -4 -5 -6 -7 -8
    cout << V-W << endl;        // prints -7 -5 -3 -1 1 3 5 7
    cout << (V<W) << endl;      // prints 1 1 1 1 0 0 0 0
    cout << V+1 << endl;        // prints 2 3 4 5 6 7 8 9
    cout << (V>3) << endl;      // prints 0 0 0 1 1 1 1 1

    IntVec T;
    T = V(0,4,2); cout << T << endl;    // prints 1 3 5 7
    T = V(2,3,1); cout << T << endl;    // prints 3 4 5
    T = V[I]; cout << T << endl;        // prints 2 4 8 3
    T = V[V>4]; cout << T << endl;      // prints 5 6 7 8

    T = V; T(1,4,2) = I;
    cout << T << endl;          // prints 1 1 3 3 5 7 7 2
    T = V; T[I] = J;
    cout << T << endl;          // prints 1 -1 -4 -2 5 6 7 -3
    T = V; T[V>4] = 0;
    cout << T << endl;          // prints 1 2 3 4 0 0 0 0
}
