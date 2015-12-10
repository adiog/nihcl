#ifndef ALLVEHICLES_H
#define ALLVEHICLES_H

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/AllVehicles.h,v 3.0 90/05/15 22:43:15 kgorlen Rel $

// AllVehicles.h -- LinkedList of all Vehicles

#ifndef MI
#define MI
#endif

#include "LinkedList.h"

class AllLink;
class Iterator;

class AllVehicles: public LinkedList {
    DECLARE_MEMBERS(AllVehicles);
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
    AllVehicles() {}
    virtual void addVehicle(AllLink&);
    virtual void removeVehicle(AllLink&);
};

#endif
