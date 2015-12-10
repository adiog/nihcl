#ifndef LANDVHCL_H
#define LANDVHCL_H

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/LandVhcl.h,v 3.0 90/05/15 22:43:38 kgorlen Rel $

#ifndef MI
#define MI
#endif

#include "Vehicle.h"

class LandVhcl: public virtual Vehicle {
    DECLARE_MEMBERS(LandVhcl);
    unsigned axles;
protected:      // storer() functions for object I/O
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
    virtual void _printOn(ostream& strm =cout) const;
public:
    LandVhcl(float h, float l, unsigned a =2) : Vehicle(h,l)
      { axles = a; }
    virtual void deepenShallowCopy();
};

#endif
