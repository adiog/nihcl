// Line.c -- Line shape

#include "Line.h"
#include "nihclIO.h"

#define THIS Line
#define BASE Shape
#define BASE_CLASSES Shape::desc()
#define MEMBER_CLASSES Point::desc()
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(Line,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Line.c,v 3.0 90/05/15 22:43:39 kgorlen Rel $",NULL,NULL);

void Line::move(const Point& d)
{
    Shape::move(d);     // move the origin
    p += d;
}

void Line::draw() const
{
    printOn();
    cout << endl;
}

bool Line::operator==(const Line& l) const
{
    if (origin() == l.origin())
        if (p == l.p) return YES;
    return NO;
}

const Class* Line::species() const  { return &classDesc; }

bool Line::isEqual(const Object& p) const
{
    return p.isSpecies(classDesc) && *this==(const Line&)p;
}

unsigned Line::hash() const
{
    return origin().hash() ^ p.hash();
}

void Line::deepenShallowCopy()
{
    Shape::deepenShallowCopy();
    p.deepenShallowCopy();
}

void Line::printOn(ostream& strm) const
{
    strm << "Line from " <<
      *TransformStack::transform.current() + origin();
    strm << " to " << *TransformStack::transform.current() + p;
}

Line::Line(OIOin& strm) : Shape(strm),p(strm) {}

void Line::storer(OIOout& strm) const
{
    Shape::storer(strm);
    p.storeMemberOn(strm);
}

Line::Line(OIOifd& fd) : Shape(fd),p(fd) {}

void Line::storer(OIOofd& fd) const
{
    Shape::storer(fd);
    p.storeOn(fd);
}
