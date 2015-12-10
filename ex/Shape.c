// Shape.c -- Abstract geometric shape class

#include "Shape.h"
#include "nihclIO.h"

#define THIS Shape
#define BASE Object
#define BASE_CLASSES Object::desc()
#define MEMBER_CLASSES Point::desc()
#define VIRTUAL_BASE_CLASSES

DEFINE_ABSTRACT_CLASS(Shape,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Shape.c,v 3.0 90/05/15 22:44:04 kgorlen Rel $",NULL,NULL);

TransformStack TransformStack::transform;
                    // shape translation stack

const Class* Shape::species() const     { return &classDesc; }

void Shape::deepenShallowCopy()
     { org.deepenShallowCopy(); }

Shape::Shape(OIOin& strm) : Object(strm),org(strm) {}

void Shape::storer(OIOout& strm) const
{
    Object::storer(strm);
    org.storeMemberOn(strm);
}

Shape::Shape(OIOifd& fd) : Object(fd),org(fd) {}

void Shape::storer(OIOofd& fd) const
{
    Object::storer(fd);
    org.storeOn(fd);
}

int Shape::compare(const Object&) const
       { shouldNotImplement("compare"); return 0; }
