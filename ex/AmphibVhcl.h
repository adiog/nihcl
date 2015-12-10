#ifndef AMPHIBVHCL_H
#define AMPHIBVHCL_H

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/AmphibVhcl.h,v 3.0 90/05/15 22:43:18 kgorlen Rel $

#ifndef MI
#define MI
#endif

#include "LandVhcl.h"
#include "WaterVhcl.h"

class AmphibVhcl: public LandVhcl, public WaterVhcl {
    DECLARE_MEMBERS(AmphibVhcl);
    unsigned axles;
protected:      // storer() functions for object I/O
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
    virtual void _printOn(ostream& strm =cout) const;
public:
    AmphibVhcl(float h, float l, float d, unsigned a =2)
        : Vehicle(h,l), LandVhcl(h,l,a), WaterVhcl(h,l,d) {}
    virtual void deepenShallowCopy();
#ifndef BUG_39
    virtual void printOn(ostream& strm =cout) const
      { Vehicle::printOn(strm); }
#endif
};

#endif
