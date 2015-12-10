#ifndef ArrayPartialH
#define ArrayPartialH

// ArrayPartial.h -- Array of Partial derivatives

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ArrayPartial.h,v 3.0 90/05/15 22:43:23 kgorlen Rel $

#include "Partial.h"

class ostream;
class Matrix;
class MatrixRow;

class ArrayPartial {
    Partial* p;
    int sz;
public:
    ArrayPartial(int siz, double*);
    ArrayPartial(int siz, Partial* =0);
    ArrayPartial(const ArrayPartial&);
    ~ArrayPartial();

    void operator=(const ArrayPartial&);
    int size() const { return sz; }
    Partial& at(int Kth) const { return p[Kth]; }
    Partial& operator[](int Kth) const;
    void operator+=(const Matrix&);

    Matrix value() const;
    Matrix jacobian() const;
    ArrayPartial operator+(const ArrayPartial&);
    friend ArrayPartial operator*(double,const ArrayPartial&);
    friend ArrayPartial operator*(const Matrix&,
                                  const ArrayPartial&);
    
    virtual void printOn(ostream& strm) const;
};
#endif /*ArrayPartialH*/
