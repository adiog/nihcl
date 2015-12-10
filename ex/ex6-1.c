// ex6-1.c -- Geometry class hierarchy

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex6-1.c,v 3.0 90/05/15 22:45:39 kgorlen Rel $

#include <iostream.h>
#include <osfcn.h>

class Point {
    int xc,yc;      // x-y coordinates
public:
    Point()                     { xc = yc = 0; }
    Point(int newx, int newy)   { xc=newx; yc=newy; }
    int x() const               { return xc; }
    int x(int newx)             { return xc = newx; }
    int y() const               { return yc; }
    int y(int newy)             { return yc = newy; }
    Point operator+(const Point& p) const {
        return Point(xc+p.xc, yc+p.yc);
    }
    void operator+=(const Point& p) {
        xc += p.x();
        yc += p.y();
    }
    void printOn(ostream& strm=cout) const;
};

void Point::printOn(ostream& strm) const
{
    strm << '(' << xc << ',' << yc << ')';
}

ostream& operator<<(ostream& strm, const Point& p) 
{
    p.printOn(strm);
    return strm;
}

class TransformStack {
    Point s[100];   // array to hold stack of points
    Point* top;     // current top of stack
public:
    TransformStack()        { top = s; }
    Point* current() const  { return top; }
    void push(Point& p) {
        Point newtop = *top + p;
        *++top = newtop;
    }
    void pop()              { top--; }
};

TransformStack transform;   // shape translation stack

class Shape {
public:
    virtual void move(const Point&) =0;
    virtual void draw() const =0;
};

class Line: public Shape {
    Point org;      // origin
    Point p;        // end point
public:
    Line(const Point& a, const Point& b) : org(a), p(b) {}
    virtual void move(const Point&);
    virtual void draw() const;
};

void Line::move(const Point& d)
{
    org += d;
    p += d;
}

void Line::draw() const
{
    cout << "Line from " << *transform.current() + org
        << " to " << *transform.current() + p << endl;
}

class Circle: public Shape {
    Point org;      // origin
    int rad;        // radius of circle
public:
    Circle(const Point& c, int r) : org(c) { rad = r; }
    virtual void move(const Point&);
    virtual void draw() const;
};

void Circle::move(const Point& d)
{
    org += d;
}

void Circle::draw() const
{
    cout << "Circle with center " << *transform.current() + org
        << " and radius " << rad << endl;
}

const unsigned PICTURE_CAPACITY = 100;

class Picture: public Shape {
    Point org;                  // origin
    Shape* s[PICTURE_CAPACITY]; // array of pointers to shapes
    int n;                      // number of shapes in this Picture
public:
    Picture() : org(0,0)        { n = 0; }  // constructor
    Picture(Point& o) : org(o)  { n = 0; }  // constructor
    void add(Shape&);                       // add Shape to Picture
    virtual void move(const Point& d)   { org += d; }
    virtual void draw() const;              // draw picture;
};

void Picture::add(Shape& t)
{
    if (n == PICTURE_CAPACITY) {
        cerr << "Picture capacity exceeded\n";
        exit(1);
    }
    s[n++] = &t;        // add pointer to Shape to Picture
}

void Picture::draw() const  // draw a Picture
{
    transform.push(org);
    for (int i=0; i<n; i++) s[i]->draw();
    transform.pop();
}

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
