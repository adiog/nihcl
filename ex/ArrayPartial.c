// ArrayPartial.c  -- array of Partial automatic derivatives

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ArrayPartial.c,v 3.0 90/05/15 22:43:22 kgorlen Rel $

/*
Author:
    S. M. Orlow
    Systex Inc.
    Beltsville, MD 20705
    301-4734-0111
    sandy@alw.nih.gov

Function:

Class ArrayPartial is a container class used with class Partial. 
The constructor, ArrayPartial::ArrayPartial(int size, double*) is 
to be used only to construct the list of independent variables
because it assumes that the number of variables is the same as the
size of the list. 
Typical usage of class ArrayPartial is:

    // NVAR = number of variables
    #define NVAR 3
    // NEQN = number of equations
    #define NEQN 3
    // x0 = vector of initial values
    double x0[] = { 1.0, 1.0, 1.0 };
        
    // X[i] is the i-th variable
    // (X[1][0],X[2][0],X[3][0]) is the solution vector
    // initial value is (1,1,1)
    ArrayPartial X(NVAR, x0);

    //f[i] is the i-th dependent variable
    ArrayPartial f(NEQN);
*/

#include <libc.h>

#include <iostream.h>

#include "ArrayPartial.h"
#include "Matrix.h"

// this constructor is only used to construct 
// set of independent functions of one variable
// assumes that siz is also the number of partials
ArrayPartial::ArrayPartial(int siz, double* pd)
{
    sz = siz;
    p = new Partial[sz];
    for(int i=0; i<sz; i++) {
      p[i].order(sz);
      p[i][0] = (pd)? *pd:0;
      p[i][i+1] = 1;  // i-th partial
      }    
}
ArrayPartial::ArrayPartial(int siz, Partial* pp)
{
    sz = siz;
    p = new Partial[sz];
    if ( pp ) {
      for(int i=0; i<sz; i++)
        p[i] = pp[i];
      }
     else
      for(int i=0; i<sz; i++)
        p[i][i+1] = 1;
}
ArrayPartial::ArrayPartial(const ArrayPartial& ap)
{
    sz=ap.sz;
    p = new Partial[sz];
    for(int i=0; i<sz; i++)
      p[i] = ap.at(i);
}
ArrayPartial::~ArrayPartial()
{
    delete p;
}

void ArrayPartial::operator=(const ArrayPartial& ap)
{
    if ( sz !=ap.sz ) {
      cerr << "operator=: ArrayPartial of size " << sz
           << " expected, " << ap.sz << " found" << endl;
      abort();
      }
    delete p;
    p = ap.p;
}

Partial& ArrayPartial::operator[](int Kth) const
{
    if ( Kth<1||Kth>sz ) {
       cerr << "operator[]: index out of range" << endl;
       abort();
       }
    return p[Kth-1];
}

void ArrayPartial::operator+=(const Matrix& argm)
{
    Matrix m = argm;
    if ( argm.nRow()==1 ) m = argm.t();
    if ( m.nCol()!=1 ) {
      cerr << "operator+=: matrix must be row or column vector"
        << endl;
      abort();
      }
    if ( m.nRow()!=sz ) {
      cerr << "operator+=: vector length " << sz
           << " expected, " << m.nRow() << " found" << endl;    
      abort();
      }
    for(int i=0; i<sz; i++)
      p[i][0] += m.at(i,0);
}
Matrix ArrayPartial::value() const
{
    Matrix val(sz,1);
    for(int i=0; i<sz; i++)
         val.at(i,0) = p[i][0];
    return val;
}
Matrix ArrayPartial::jacobian() const
{
    Matrix val(sz,sz);
    for(int i=0; i<sz; i++)
      for(int j=0; j<sz; j++)
         val.at(i,j) = p[i][j+1];
    return val;
}
ArrayPartial ArrayPartial::operator+(const ArrayPartial& ap)
{
    if ( size() != ap.size() ) {
      cerr << "operator+: ArrayPartial of size " << size()
           << " expected, " << ap.size() << " found" << endl;
      abort();
      }
    ArrayPartial val(sz);
    for(int i=0; i<sz; i++)
      val.at(i) = p[i] + ap.at(i);
    return val;
}
ArrayPartial operator*(double d,const ArrayPartial& ap)
{
    ArrayPartial val(ap.size());
    for(int i=0;i<ap.size(); i++)
       val.at(i) = d*ap.at(i);
    return val;
}
ArrayPartial operator*(const Matrix& m, const ArrayPartial& ap)
{
    if ( ap.size()!=m.nCol() ) {
      cerr << "operator* mismatch: "
           << m.nRow() << "x" << m.nCol() << " matrix and " 
           << ap.size() << " ArrayPartial" << endl;
      abort();
      }
    ArrayPartial val(ap.size());
    for(int i=0; i< ap.size(); i++) {
      Partial tmp;
      for(int j=0; j<m.nCol(); j++ )
        tmp = tmp + m.at(i,j)*ap.at(j);
      val.at(i) = tmp;
      }
    return val;
}
void ArrayPartial::printOn(ostream& strm) const
{
    strm << "ArrayPartial[" << endl;
    for(int i=0; i<sz; i++)
      strm << p[i] << endl;
    strm << "]" << endl;
}
