#ifndef PICTURE_H
#define PICTURE_H

// Picture.h -- A container for Shapes

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Picture.h,v 3.0 90/05/15 22:44:00 kgorlen Rel $

#include "Shape.h"
#include "OrderedCltn.h"

class Picture: public Shape {
    DECLARE_MEMBERS(Picture);
    OrderedCltn s;      // collection of pointers to shapes
protected:              // storer() functions for object I/O
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
public:
    Picture() : Shape(Point(0,0)) {}
    Picture(Point& org) : Shape(org) {}
    bool operator==(const Picture&) const;
    bool operator!=(const Picture& a) const { return !(*this==a); }
    void add(Shape&);   // add Shape to Picture
    virtual void draw() const;
    virtual void deepenShallowCopy();
    virtual unsigned hash() const;
    virtual bool isEqual(const Object&) const;
    virtual void printOn(ostream& strm =cout) const;
    virtual const Class* species() const;
};

#endif
