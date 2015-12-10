//  AutoDeriv.c -- one dimensional automatic derivative

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/AutoDeriv.c,v 3.0 90/05/15 22:43:24 kgorlen Rel $
/*
Author:
    S.M.Orlow
    Systex, Inc.
    Beltsville, MD 20705
    301-474-0111
    sandy@alw.nih.gov
*/

#include <iostream.h>
#include "AutoDeriv.h"

void AutoDeriv::operator=(const AutoDeriv& x) 
{
    u=F(x); du=dF(x);
}
int AutoDeriv::operator==(const AutoDeriv& x) const
{
    return (u==F(x)&&du==dF(x));
}

AutoDeriv AutoDeriv::operator-() const
{
    return AutoDeriv(-u,-du);
}

AutoDeriv AutoDeriv::pow(int k) const
{
    if ( k==0 )  return AutoDeriv(1,0);
   else if ( k==1 )  return *this;
   else if ( k>1 )   return (*this)*(this->pow(k-1));
   else    /*k<0*/   return AutoDeriv(1,0)/this->pow(-k);
}

void AutoDeriv::printOn(ostream& strm) const
{
    strm << "[" << u << "," << du << "]";
}
ostream& operator<<(ostream& strm, const AutoDeriv& x)
{
    x.printOn(strm);
    return strm;
}
