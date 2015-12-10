#ifndef PartialH
#define PartialH

// Partial.h -- partial derivative vector

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Partial.h,v 3.0 90/05/15 22:43:55 kgorlen Rel $

#include <math.h>

class ostream;

// MAX_ORD is the maximum number of Partial derivatives
// It is possible to make this choice at run-time but
// doing it this way improves speed of computation
#define MAX_ORD 64

class Partial {
private:
    int ord; // current order
    double du[MAX_ORD+1];    // array of Partial derivative values
public:
    Partial();
    Partial(double val,int neword =0);
    Partial(const Partial&);

    int order() const { return ord; }
    int order(int neword);

    void operator=(const Partial&);
    void operator=(double val) { du[0] = val;}
    double& operator[](int i) const { return du[i]; }
    Partial operator-() const;
    Partial pow(int) const;

    friend Partial operator+(const Partial&,const Partial&);
    friend Partial operator-(const Partial&,const Partial&);
    friend Partial operator*(const Partial&,const Partial&);
    friend Partial operator/(const Partial&,const Partial&);

    friend Partial exp(const Partial& x);
    friend Partial log(const Partial& x);
    friend Partial sin(const Partial& x);
    friend Partial cos(const Partial& x);
    void printOn(ostream&) const;
};

extern ostream& operator<<(ostream&,const Partial&);
#endif/* PartialH*/
