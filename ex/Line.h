#ifndef LINE_H
#define LINE_H

// Line.h -- Line shape

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Line.h,v 3.0 90/05/15 22:43:40 kgorlen Rel $

#include "Shape.h"

class Line: public Shape {
    DECLARE_MEMBERS(Line);
    Point p;            // end point
protected:              // storer() functions for object I/O
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
public:
    Line(const Point& a, const Point& b) : Shape(a), p(b) {}
    bool operator==(const Line&) const;
    bool operator!=(const Line& a) const    { return !(*this==a); }
    virtual void move(const Point& d);
    virtual void draw() const;
    virtual void deepenShallowCopy();
    virtual unsigned hash() const;
    virtual bool isEqual(const Object&) const;
    virtual void printOn(ostream& strm =cout) const;
    virtual const Class* species() const;
};

#endif
