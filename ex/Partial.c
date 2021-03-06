//  Partial.c --  vector of partial derivatives

//$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Partial.c,v 3.0 90/05/15 22:43:54 kgorlen Rel $

/*
Author:
    S.M.Orlow
    Systex, Inc.
    Beltsville, MD 20705
    301-474-0111
    sandy@alw.nih.gov

Function:

Class Partial implements a method of computing an arbitrary
number of partial derivatives from a known function. The
function must be realizable as a syntactically correct
expression for the C-language.  Analytically, the function must
be a member of the set of functions generated by a fixed number
of independent variables, and exp, log, sin, and cos and closed
under rational operations and function composition.

The number (order) of independent variables (partial
derivatives) is set by constructors. This number is restricted
to be <= the maximum order, MAX_ORD, which may be changed by
recompiling Partial.c.

The member variable, 'du', will be an array of MAX_ORD+1 double
values representing one function value and a list of partial
derivative values.  Class Partial has been implemented in this
way, rather than using dynamic allocation to allow for an
indeterminate number of variables, to improve speed of execution
of member functions by eliminating the need for repeated call to
allocate/free memory each time a Partial object is constructed.

Class Partial is not intended to be used directly in an
application program. Instead class ArrayPartial should be used
to construct multiple Partial objects.

*/

#include <libc.h>
#include <iostream.h>
#include "Partial.h"

void err_exit(char* msg) 
{
    cerr << " Partial: " << msg << endl;
    abort();
}

int max_order(const Partial& x, const Partial& y)
{
    int xord = x.order(), yord=y.order();
    return (xord>yord)? xord:yord;
}
Partial::Partial()
{
    ord = -1;
    for(int i=0; i<=MAX_ORD; i++)
      du[i] = 0;
}
int Partial::order(int neword)
{
    if ( ord>=0 ) err_exit("can't reassign order");
    return (ord=neword);
}
Partial::Partial(double val,int neword)
{
    if ( (neword<0)||(neword>MAX_ORD) )
      err_exit("order out of bounds");
    for(int i=0; i<=MAX_ORD; i++)
      du[i] = 0;
    ord = neword;
    du[0] = val;    
}
    
Partial::Partial(const Partial& x) 
{
    *this = x;
}

void Partial::operator=(const Partial& x) 
{
    ord = x.ord;
        for(int i=0; i<=MAX_ORD; i++)
       if ( i<=ord ) du[i] = x[i];
        else du[i] = 0;
}
    
Partial operator+(const Partial& x,const Partial& y) 
{
    Partial v(0,max_order(x,y));
    for(int i=0; i<=v.order(); i++) 
       v[i] = x[i]+y[i];
    return v;
}
Partial operator-(const Partial&x, const Partial& y) 
{
    return (x + (-y));
}
Partial operator*(const Partial& x,const Partial& y) 
{
    Partial v(x[0]*y[0],max_order(x,y));
    for(int i=1; i<=v.order(); i++)
       v[i] = x[0]*y[i] + x[i]*y[0];
    return v;
}
Partial operator/(const Partial& x,const Partial& y) 
{
    if ( y[0] == 0 ) err_exit("division by zero");
    Partial v(x[0]/y[0],max_order(x,y));
    for(int i=1; i<=v.order(); i++) 
       v[i] = (y[0]*x[i] - x[0]*y[i])/(y[0]*y[0]);
    return v;
}

Partial Partial::operator-() const 
{
    Partial v(0,ord);
    for(int i=0; i<=ord; i++)
      v[i] = - du[i];
    return v;
}

Partial Partial::pow(int k) const 
{
    if ( k==0 ) return Partial(1.0);
    if ( k==1 ) return *this;

    Partial v(*this);
    double du0k_1 = 1;        // to hold (k-1)th power
    for(int kk=1; kk<=k-1; kk++)
      du0k_1 *= du[0];
    v[0] = du0k_1*du[0];        // kth power
    for(int i=1; i<=ord; i++)
        v[i] = k*du0k_1*du[i];
    return v;
}

void Partial::printOn(ostream& strm) const
{
    strm << "[";
    for(int i=0; i<=ord; i++) {
      strm << du[i];
      if ( i<ord ) strm << " ";
      }
    strm << "]";
}

ostream& operator<<(ostream& strm, const Partial& p)
{
    p.printOn(strm);
    return strm;
}
Partial exp(const Partial& x) 
{
    Partial v(::exp(x[0]),x.order());
    for(int i=1; i<=x.order(); i++)
      v[i] = x[i]*v[0];    // d(exp(F)) = dF*exp(F)
    return v;
}
Partial log(const Partial& x) 
{
    if ( x[0] == 0 ) err_exit("0 argument for log");
    Partial v(::log(x[0]),x.order());
    for(int i=1; i<=x.order(); i++)
      v[i] = x[i]/x[0];
    return v;
}
Partial sin(const Partial& x) {
    Partial v(::sin(x[0]),x.order());
    double cosx = ::cos(x[0]);
    for(int i=1; i<=x.order(); i++)
      v[i] = x[i]*cosx;
    return v;
}
Partial cos(const Partial& x) {
    Partial v(::cos(x[0]),x.order());
    double sinx = ::sin(x[0]);
    for(int i=1; i<=x.order(); i++)
      v[i] = -x[i]*sinx;
    return v;
}
