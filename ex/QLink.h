#ifndef QLINK_H
#define QLINK_H

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/QLink.h,v 3.0 90/05/15 22:44:02 kgorlen Rel $

// QLink.h -- Link used by Vehicle queue LinkedLists

#ifndef MI
#define MI
#endif

#include "Link.h"

class QLink: public Link {
    DECLARE_MEMBERS(QLink);
protected:
    QLink() {};
public:
    virtual int compare(const Object&) const = 0;
    virtual unsigned hash() const = 0;
    virtual bool isEqual(const Object&) const = 0;
    virtual void printOn(ostream& strm =cout) const = 0;
};

#endif
