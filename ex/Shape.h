#ifndef SHAPE_H
#define SHAPE_H

// Shape.h -- Abstract geometric shape class

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Shape.h,v 3.0 90/05/15 22:44:05 kgorlen Rel $

#include "Object.h"
#include "Point.h"
#include "Stack.h"

class Shape: public Object {
    DECLARE_MEMBERS(Shape);
    Point org;          // origin
protected:              // storer() functions for object I/O
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
protected:
    Shape(const Point& p) : org(p)  {}
public:
    Point origin() const                { return org; }
    virtual void move(const Point& d)   { org += d; }
    virtual void draw() const = 0;
    virtual void deepenShallowCopy();
    virtual unsigned hash() const = 0;
    virtual bool isEqual(const Object&) const = 0;
    virtual void printOn(ostream& strm =cout) const = 0;
    virtual const Class* species() const;
private:                // shouldNotImplement()
    virtual int compare(const Object&) const;
};

class TransformStack {
public:
    static TransformStack transform;    // shape translation stack
private:
    Stack s;
public:
    TransformStack()        { s.push(*new Point(0,0)); }
    Point* current() const  { return (Point*)s.top(); }
    void push(Point& p)     { s.push(*new Point(*current() + p)); }
    void pop()              { delete (Point*)s.pop(); }
};

#endif
