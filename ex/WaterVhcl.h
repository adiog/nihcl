#ifndef WATERVHCL_H
#define WATERVHCL_H

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/WaterVhcl.h,v 3.0 90/05/15 22:44:14 kgorlen Rel $

#ifndef MI
#define MI
#endif

#include "Vehicle.h"

class WaterVhcl: public virtual Vehicle {
    DECLARE_MEMBERS(WaterVhcl);
    float draft;
protected:      // storer() functions for object I/O
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
    virtual void _printOn(ostream& strm =cout) const;
public:
    WaterVhcl(float h, float l, float d) : Vehicle(h,l)
      { draft = d; }
    virtual void deepenShallowCopy();
};

#endif
