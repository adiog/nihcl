#ifndef ALLLINK_H
#define ALLLINK_H

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/AllLink.h,v 3.0 90/05/15 22:43:13 kgorlen Rel $

// AllLink.h -- Link used by AllVehicles LinkedList

#ifndef MI
#define MI
#endif

#include "Link.h"

class AllLink: public Link {
    DECLARE_MEMBERS(AllLink);
protected:
    AllLink() {};
public:
    virtual int compare(const Object&) const = 0;
    virtual unsigned hash() const = 0;
    virtual bool isEqual(const Object&) const = 0;
    virtual void printOn(ostream& strm =cout) const = 0;
};

#endif
