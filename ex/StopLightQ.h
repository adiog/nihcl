#ifndef STOPLIGHTQ_H
#define STOPLIGHTQ_H

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/StopLightQ.h,v 3.0 90/05/15 22:44:07 kgorlen Rel $

// StopLightQ.h -- Stop Light Vehicle Queue LinkedList

#ifndef MI
#define MI
#endif

#include "VehicleQ.h"

class LandVhcl;

class StopLightQ: public VehicleQ {
    DECLARE_MEMBERS(StopLightQ);
#ifndef BUG_38
// internal <<AT&T C++ Translator 2.00 06/30/89>> error: bus error (or something nasty like that)
protected:              // storer() functions for object I/O
    virtual void storer(OIOofd& fd) const
      { VehicleQ::storer(fd); };
    virtual void storer(OIOout& strm) const
      { VehicleQ::storer(strm); };
#endif
public:
    StopLightQ() {}
    virtual void addVehicle(LandVhcl&);
};

#endif
