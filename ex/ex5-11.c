// ex5-11.c -- Using automatic derivatives
//	       to solve systems of equations

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex5-11.c,v 3.0 90/05/15 22:45:14 kgorlen Rel $

#include <iostream.h>
#include <iomanip.h>
#include "ArrayPartial.h"
#include "Matrix.h"

void print_iteration(int count,const ArrayPartial& X)
{
    if ( count==0 )
      cout << "INITIAL VALUES" << endl;
    else
      cout << "VALUES FROM ITERATION #" << count << endl;
    cout << setiosflags(ios::showpos|ios::uppercase|
                      ios::scientific) 
         << setprecision(11);
    cout << "X = " << X[1][0] << endl
         << "Y = " << X[2][0] << endl
         << "Z = " << X[3][0] << endl
         << endl;
}
void print_function(const ArrayPartial& Y)
{
    cout << setiosflags(ios::showpos|ios::uppercase|
                      ios::scientific) 
         << setprecision(11);
    cout << "FUNCTION VALUES" << endl
         << "F(X,Y,Z) = " << Y[1][0] << endl
         << "G(X,Y,Z) = " << Y[2][0] << endl
         << "H(X,Y,Z) = " << Y[3][0] << endl
         << endl;
}

void print_correction(const Matrix& v)
{
    cout << setiosflags(ios::showpos|ios::uppercase|
                      ios::scientific) 
         << setprecision(11);
    cout << "CORRECTION VECTOR" << endl
         << "X = " << v(0,0) << endl
         << "Y = " << v(1,0) << endl
         << "Z = " << v(2,0) << endl
         << endl;
}

// NVAR = number of independent variables
static const int NVAR = 3;
// NEQN = number of equations
static const int NEQN = 3;
// NITER = number of iterations
static const int NITER = 16;
// DELTA = convergence threshhold
static const double DELTA =1.0E-12;
// x0 = initial values of independent variables
static double x0[] = { 1, 1, 1 };

main()
{
  // X[i] is the i-th variable
  // (X[1][0],X[2][0],X[3][0]) is the solution vector
  // initial value is (1.0,1.0,1.0)
  ArrayPartial X(NVAR, x0);

  // correction vector
  Matrix del(NVAR/*rows*/,1/*columns*/);

  int count =0;
  while(count <=NITER) {
    print_iteration(count++,X);

    // define 3 equations in 3 variables
    // (f[1][0],f[2][0],f[3][0]) is the function value vector
    // ( f[i][j] ) is the jacobian matrix
    ArrayPartial f(NEQN);
    f[1]= 16.0*X[1].pow(4) + 16.*X[2].pow(4) + X[3].pow(4) - 16.0;
    f[2]=      X[1].pow(2) +     X[2].pow(2) + X[3].pow(2) -  3.0;
    f[3]=      X[1].pow(3) -     X[2];

    print_function(f);

    // recompute jacobian and new correction vector
    Matrix J = f.jacobian();
    Matrix v = f.value();
    del = -(~J*v);

    print_correction(del);
    if ( norm(del) < DELTA ) break;

    // compute next estimate for solution
    // (X[1][0],X[2][0],X[3][0])
    X += del;
    }
}
