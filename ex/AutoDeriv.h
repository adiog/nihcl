#ifndef AutoDerivH
#define AutoDerivH

// AutoDeriv.h -- one-dimensional automatic derivative

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/AutoDeriv.h,v 3.0 90/05/15 22:43:25 kgorlen Rel $

#include <math.h>

class ostream;

class AutoDeriv {
private:
    double u,du;
public:
    AutoDeriv(double v = 0.0,double dv = 0.0) { u=v; du=dv; }

    friend double F(const AutoDeriv& x) { return x.u; }
    friend double dF(const AutoDeriv& x) { return x.du; }

    void operator=(const AutoDeriv& x);
    int operator==(const AutoDeriv& x) const;

    AutoDeriv operator-() const;
    AutoDeriv pow(int e) const;

    friend AutoDeriv operator+(const AutoDeriv&,
                               const AutoDeriv&);
    friend AutoDeriv operator-(const AutoDeriv&,
                               const AutoDeriv&);
    friend AutoDeriv operator*(const AutoDeriv&,
                               const AutoDeriv&);
    friend AutoDeriv operator/(const AutoDeriv&,
                               const AutoDeriv&);
    void printOn(ostream& strm) const;
};
inline AutoDeriv operator+(const AutoDeriv& x,
                           const AutoDeriv& y)
{ 
    return AutoDeriv(F(x)+F(y),dF(x)+dF(y)); 
}
inline AutoDeriv operator-(const AutoDeriv& x,
                           const AutoDeriv& y)
{ 
    return AutoDeriv(F(x)-F(y),dF(x)-dF(y)); 
}
inline AutoDeriv operator*(const AutoDeriv& x,
                           const AutoDeriv& y)
{
    return AutoDeriv(F(x)*F(y),
                     F(y)*dF(x)+F(x)*dF(y));
}
inline AutoDeriv operator/(const AutoDeriv& x,
                           const AutoDeriv& y)
{ 
    return AutoDeriv(F(x)/F(y),
                     (F(y)*dF(x)-F(x)*dF(y))/F(y)*F(y)); 
}
inline AutoDeriv Exp(const AutoDeriv& x) 
{ 
    return AutoDeriv(exp(F(x)),dF(x)*exp(F(x))); 
}
inline AutoDeriv Log(const AutoDeriv& x) 
{ 
    return AutoDeriv(log(F(x)),dF(x)/F(x)); 
}
inline AutoDeriv Sin(const AutoDeriv& x) 
{ 
    return AutoDeriv(sin(F(x)),dF(x)*cos(F(x))); 
}
inline AutoDeriv Cos(const AutoDeriv& x) 
{ 
    return AutoDeriv(cos(F(x)),-dF(x)*sin(F(x))); 
}
extern ostream& operator<<(ostream& strm, 
                           const AutoDeriv& x);
#endif/* AutoDerivH */
