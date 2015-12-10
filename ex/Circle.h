#ifndef CIRCLE_H
#define CIRCLE_H

// Circle.h -- Circle shape

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Circle.h,v 3.0 90/05/15 22:43:30 kgorlen Rel $

#include "Shape.h"

class Circle: public Shape {
    DECLARE_MEMBERS(Circle);
    int rad;            // radius of circle
protected:              // storer() functions for object I/O
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
public:
    Circle(const Point& c, int r) : Shape(c) { rad = r; }
    bool operator==(const Circle&) const;
    bool operator!=(const Circle& a) const { return !(*this==a); }
    virtual void draw() const;
    virtual unsigned hash() const;
    virtual bool isEqual(const Object&) const;
    virtual void printOn(ostream& strm =cout) const;
    virtual const Class* species() const;
};

#endif
