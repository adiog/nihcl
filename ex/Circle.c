// Circle.c -- Circle shape

#include "Circle.h"
#include "nihclIO.h"

#define THIS Circle
#define BASE Shape
#define BASE_CLASSES Shape::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(Circle,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Circle.c,v 3.0 90/05/15 22:43:29 kgorlen Rel $",NULL,NULL);

void Circle::draw() const
{
    printOn();
    cout << endl;
}

bool Circle::operator==(const Circle& c) const
{
    if (origin() == c.origin())
        if (rad == c.rad) return YES;
    return NO;
}

const Class* Circle::species() const    { return &classDesc; }

bool Circle::isEqual(const Object& p) const
{
    return p.isSpecies(classDesc) && *this==(const Circle&)p;
}

unsigned Circle::hash() const
{
    return origin().hash() ^ rad;
}

void Circle::printOn(ostream& strm) const
{
    strm << "Circle with center " <<
      *TransformStack::transform.current() + origin();
    strm << " and radius " << rad;
}

Circle::Circle(OIOin& strm)
    : Shape(strm)
{
    strm >> rad;
}

void Circle::storer(OIOout& strm) const
{
    Shape::storer(strm);
    strm << rad;
}

Circle::Circle(OIOifd& fd)
    : Shape(fd)
{
    fd >> rad;
}

void Circle::storer(OIOofd& fd) const
{
    Shape::storer(fd);
    fd << rad;
}
