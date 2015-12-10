// Picture.c -- A container for Shapes

#include "Picture.h"
#include "nihclIO.h"

#define THIS Picture
#define BASE Shape
#define BASE_CLASSES Shape::desc()
#define MEMBER_CLASSES OrderedCltn::desc()
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(Picture,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Picture.c,v 3.0 90/05/15 22:43:59 kgorlen Rel $",NULL,NULL);

void Picture::add(Shape& t)
{
    s.add(t);   // calls OrderedCltn::add()
}

void Picture::draw() const
{
    printOn();
}

bool Picture::operator==(const Picture& p) const
{
    if (origin() == p.origin())
        if (s == p.s) return YES;
    return NO;
}

const Class* Picture::species() const   { return &classDesc; }

bool Picture::isEqual(const Object& p) const
{
    return p.isSpecies(classDesc) && *this==(const Picture&)p;
}

unsigned Picture::hash() const
{
    return origin().hash() ^ s.hash();
}

void Picture::deepenShallowCopy()
{
    Shape::deepenShallowCopy();
    s.deepenShallowCopy();
}

void Picture::printOn(ostream& strm) const
{
    TransformStack::transform.push(origin());
    for (int i=0; i<s.size(); i++) {
        ((Shape*)s[i])->printOn(strm);
        strm << endl;
    }
    TransformStack::transform.pop();
}

Picture::Picture(OIOin& strm) : Shape(strm),s(strm) {}

void Picture::storer(OIOout& strm) const
{
    Shape::storer(strm);
    s.storeMemberOn(strm);
}

Picture::Picture(OIOifd& fd) : Shape(fd),s(fd) {}

void Picture::storer(OIOofd& fd) const
{
    Shape::storer(fd);
    s.storeOn(fd);
}
