#ifndef VEHICLEQ_H
#define VEHICLEQ_H

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/VehicleQ.h,v 3.0 90/05/15 22:44:12 kgorlen Rel $

// VehicleQ.h -- Vehicle Queue LinkedList

#ifndef MI
#define MI
#endif

#include "LinkedList.h"

class QLink;
class Iterator;

class VehicleQ: public LinkedList {
    DECLARE_MEMBERS(VehicleQ);
#ifndef BUG_38
// internal <<AT&T C++ Translator 2.00 06/30/89>> error: bus error (or something nasty like that)
protected:              // storer() functions for object I/O
    virtual void storer(OIOofd& fd) const
      { LinkedList::storer(fd); };
    virtual void storer(OIOout& strm) const
      { LinkedList::storer(strm); };
#endif
protected:
    virtual Link& linkCastdown(Object&) const;
public:
    VehicleQ() {}
    virtual void addVehicle(QLink&);
    virtual void removeVehicle(QLink&);
};

#endif
