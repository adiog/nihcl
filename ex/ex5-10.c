// ex5-10 -- one dimensional automatic derivatives with
//           class AutoDeriv

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex5-10.c,v 3.0 90/05/15 22:45:12 kgorlen Rel $

#include <math.h>
#include <iostream.h>
#include "AutoDeriv.h"

const double halfPI = M_PI_2; /* M_PI_2 from math.h */

main()
{
    AutoDeriv W(0,1);
    AutoDeriv Y_plus = W+1;
    AutoDeriv Y_times= W*2;
    AutoDeriv Z = 2*W*(W+2) + W + 1;
    cout << "W=" << W << endl;
    cout << "W+1=" << Y_plus << endl;
    cout << "W*2=" << Y_times << endl;
    cout << "Z = 2*W*(W+2)+W+1="<< Z << endl;
    cout << "(2*(W+1)).pow(3)=" << (2*(W+1)).pow(3) << endl;
    cout << "2*W*Z.pow(2)=" << 2*W*Z.pow(2) << endl;
    cout << endl;

    // evaluate 2*x*(sin(x)+1) at x=0
    AutoDeriv X(0,1);
    AutoDeriv Y = 2*X*(Sin(X)+1);

    cout << "let  X = [F(X),dF(X)] = "
         << "[" << F(X)  << "," << dF(X) << "]" 
         << endl;
    cout << "let  Y = 2*X*(Sin(X)+1)" << "\n"
         << "then Y = [F(Y),dF(Y)] = "
         << "[" << F(Y)  << "," << dF(Y) << "]" 
         << endl<< endl;
    
    // evaluate 2*x*(sin(x)+1) at x=halfPI
    AutoDeriv U(halfPI,1); 
    AutoDeriv V = 2*U*(Sin(U)+1);

    cout << "let  U = [F(U),dF(U)] = "
         << "[" << F(U)  << "," << dF(U) << "]" 
         << endl;
    cout << "let  V = 2*U*(Sin(U)+1)" << "\n"
         << "then V = [F(V),dF(V)] = "
         << "[" << F(V)  << "," << dF(V) << "]" 
         << endl;
}
