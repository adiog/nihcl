// ex7-1.c -- Geometry class hierarchy using NIH Class Library

#include "Point.h"
#include "Stack.h"
#include "OrderedCltn.h"

class TransformStack {
    Stack s;
public:
    TransformStack()        { s.push(*new Point(0,0)); }
    Point* current() const  { return (Point*)s.top(); }
    void push(Point& p)     { s.push(*new Point(*current() + p)); }
    void pop()              { delete (Point*)s.pop(); }
};

TransformStack transform;   // shape translation stack

class Shape: public Object {
    DECLARE_MEMBERS(Shape);
    Point org;          // origin
protected:
    Shape(const Point& p) : org(p)  {}
public:
    Point origin() const                { return org; }
    virtual void move(const Point& d)   { org += d; }
    virtual void draw() const = 0;
private:                // shouldNotImplement()
    virtual int compare(const Object&) const;
    virtual unsigned hash() const;
    virtual bool isEqual(const Object&) const;
    virtual void printOn(ostream& strm =cout) const;
protected:              // shouldNotImplement()
    virtual void deepenShallowCopy();
};

#define THIS Shape
#define BASE Object
#define BASE_CLASSES Object::desc()
#define MEMBER_CLASSES Point::desc()
#define VIRTUAL_BASE_CLASSES

DEFINE_ABSTRACT_CLASS(Shape,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex7-1.c,v 3.0 90/05/15 22:45:47 kgorlen Rel $",NULL,NULL);

#undef  THIS
#undef  BASE
#undef  BASE_CLASSES
#undef  MEMBER_CLASSES
#undef  VIRTUAL_BASE_CLASSES

class Line: public Shape {
    DECLARE_MEMBERS(Line);
    Point p;            // end point
public:
    Line(const Point& a, const Point& b) : Shape(a), p(b) {}
    virtual void move(const Point&);
    virtual void draw() const;
};

#define THIS Line
#define BASE Shape
#define BASE_CLASSES Shape::desc()
#define MEMBER_CLASSES Point::desc()
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(Line,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex7-1.c,v 3.0 90/05/15 22:45:47 kgorlen Rel $",NULL,NULL);

void Line::move(const Point& d)
{
    Shape::move(d);
    p += d;
}

void Line::draw() const
{
    cout << "Line from " << *transform.current() + origin()
         << " to " << *transform.current() + p << endl;
}

#undef  THIS
#undef  BASE
#undef  BASE_CLASSES
#undef  MEMBER_CLASSES
#undef  VIRTUAL_BASE_CLASSES

class Circle: public Shape {
    DECLARE_MEMBERS(Circle);
    int rad;            // radius of circle
public:
    Circle(const Point& c, int r) : Shape(c) { rad = r; }
    virtual void draw() const;
};

#define THIS Circle
#define BASE Shape
#define BASE_CLASSES Shape::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(Circle,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex7-1.c,v 3.0 90/05/15 22:45:47 kgorlen Rel $",NULL,NULL);

void Circle::draw() const
{
    cout << "Circle with center "
         << *transform.current() + origin()
         << " and radius " << rad << endl;
}

#undef  THIS
#undef  BASE
#undef  BASE_CLASSES
#undef  MEMBER_CLASSES
#undef  VIRTUAL_BASE_CLASSES

class Picture: public Shape {
    DECLARE_MEMBERS(Picture);
    OrderedCltn s;      // collection of pointers to shapes
public:
    Picture() : Shape(Point(0,0)) {}    // constructor
    Picture(Point& org) : Shape(org) {} // constructor
    void add(Shape&);                   // add Shape to Picture
    virtual void draw() const;          // draw picture;
};

#define THIS Picture
#define BASE Shape
#define BASE_CLASSES Shape::desc()
#define MEMBER_CLASSES OrderedCltn::desc()
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(Picture,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex7-1.c,v 3.0 90/05/15 22:45:47 kgorlen Rel $",NULL,NULL);

void Picture::add(Shape& t)
{
    s.add(t);           // calls OrderedCltn::add()
}

void Picture::draw() const      // draw a Picture
{
    transform.push(origin());
    for (int i=0; i<s.size(); i++)  // s.size() is # of
                                    // objects in s
        ((Shape*)s[i])->draw();     // cast address of ith object
                                    // to Shape* and call draw()
    transform.pop();
}

#undef  THIS
#undef  BASE
#undef  BASE_CLASSES
#undef  MEMBER_CLASSES
#undef  VIRTUAL_BASE_CLASSES

main()
{
    Line l(Point(1,2),Point(3,4));  // create a Line
    Circle c(Point(5,6),1);         // create a Circle
    l.draw();                       // draw the line
    c.draw();                       // draw the circle
    Picture p;                      // create an empty Picture
    l.move(Point(1,0));             // move the line
    p.add(l);                       // add the line to the picture
    c.move(Point(1,0));             // move the circle
    p.add(c);                       // add it to the picture
    p.draw();                       // draw the picture
    p.move(Point(10,10));           // translate it by (10,10)
    p.draw();                       // draw it again

    Picture bigPic;
    Picture littlePic1, littlePic2(*new Point(10,10));
    littlePic1.add(*new Line(Point(1,1),Point(2,2)));
    littlePic1.add(*new Circle(Point(3,3),1));
    littlePic2.add(*new Line(Point(4,4),Point(5,5)));
    littlePic2.add(*new Circle(Point(3,3),2));
    littlePic2.move(Point(1,1));
    bigPic.add(littlePic1);
    bigPic.add(littlePic2);
    bigPic.draw();
}

// Dummy definitions for functions required by NIH Class Library

int Shape::compare(const Object&) const
       { shouldNotImplement("compare"); return 0; }
void Shape::deepenShallowCopy()
       { shouldNotImplement("deepenShallowCopy"); }
unsigned Shape::hash() const
       { shouldNotImplement("hash"); return 0; }
bool Shape::isEqual(const Object&) const
       { shouldNotImplement("isEqual"); return 0; }
void Shape::printOn(ostream&) const
       { shouldNotImplement("printOn"); }
Shape::Shape(OIOifd& fd) : Object(fd) {}
Shape::Shape(OIOin& strm) : Object(strm) {}

Line::Line(OIOifd& fd) : Shape(fd) {}
Line::Line(OIOin& strm) : Shape(strm) {}

Circle::Circle(OIOifd& fd) : Shape(fd) {}
Circle::Circle(OIOin& strm) : Shape(strm) {}

Picture::Picture(OIOifd& fd) : Shape(fd) {}
Picture::Picture(OIOin& strm) : Shape(strm) {}
