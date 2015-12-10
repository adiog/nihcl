// ArrayOb.c -- Basic polymorphic array of objects

#include <malloc.h>
#include "ArrayOb.h"
#include "nihclIO.h"

#define THIS    ArrayOb
#define BASE    Collection
#define BASE_CLASSES Collection::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(ArrayOb,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ArrayOb.c,v 3.0 90/05/15 22:43:20 kgorlen Rel $",NULL,NULL);

extern const int NIHCL_ALLOCSIZE, NIHCL_INDEXRANGE;

ArrayOb::ArrayOb(unsigned size)
{
    sz = size;
    if (sz==0) allocSizeErr();
    v = new Object*[sz];
    register i = sz;
    register Object** vp = v;
    while (i--) *vp++ = nil;
}
    
ArrayOb::ArrayOb(const ArrayOb& a)
{
    register i = a.sz;
    sz = i;
    v = new Object*[i];
    register Object** vp = v;
    register Object** av = a.v;
    while (i--) *vp++ = *av++;
}

void ArrayOb::operator=(const ArrayOb& a)
{
    if (v != a.v) {
        delete v;
        v = new Object*[sz=a.sz];
        register i = a.sz;
        register Object** vp = v;
        register Object** av = a.v;
        while (i--) *vp++ = *av++;
    }
}

bool ArrayOb::operator==(const ArrayOb& a) const
{
    if (sz != a.sz) return NO;
    register unsigned i = sz;
    register Object** vp = v;
    register Object** av = a.v;
    while (i--) {
        if (!((*vp++)->isEqual(**av++))) return NO;
    }
    return YES;
}

const Class* ArrayOb::species() const { return &classDesc; }

bool ArrayOb::isEqual(const Object& a) const
{
    return a.isSpecies(classDesc) && *this==(const ArrayOb&)a;
}

unsigned ArrayOb::hash() const
{
    register unsigned h = sz;
    register unsigned i = sz;
    register Object** vp = v;
    while (i--) h^=(*vp++)->hash();
    return h;
}

void ArrayOb::deepenShallowCopy()
{
    BASE::deepenShallowCopy();
    register i = sz;
    register Object** vp = v;
    while (i--) {
        *vp = (*vp)->deepCopy();
        vp++;
    }
}

Collection& ArrayOb::addContentsTo(Collection& cltn) const
{
    register Object** vp = v;
    register unsigned i = sz;
    while (i--) cltn.add(**vp++);
    return cltn;
}

Object*& ArrayOb::at(int i)         { return (*this)[i]; }

const Object *const& ArrayOb::at(int i) const
    { return (*this)[i]; }

unsigned ArrayOb::capacity() const  { return sz; }
    
int ArrayOb::compare(const Object& arg) const
// Compare two arrays of objects.  If *this > arg return >0,
// *this == arg return 0, and if *this < arg return <0.
{
    assertArgSpecies(arg,classDesc,"compare");
    ArrayOb& a = (ArrayOb&)arg;
    for (int i=0; i<sz; i++) {
// previous elements compared equal;
// longer ArrayOb is therefore larger
        if (i == a.sz) return 1;
// compare() != 0 at any element determines ordering
        int val;
        if ((val = v[i]->compare(*a.v[i])) != 0) return val;
    }
// all elements in this ArrayOb compare() equal to arg ArrayOb
    if (sz == a.sz) return 0;
    return -1;
}

Object* ArrayOb::doNext(Iterator& pos) const
{
    if (pos.index < size()) return v[pos.index++];
    return 0;
}

void ArrayOb::reSize(unsigned newsize)
{
    if (newsize == 0) allocSizeErr();
    v = (Object**)realloc((char*)v,newsize*sizeof(Object*));
    if (newsize > sz) {     // initialize new space to nil
        Object** vp = &v[sz];
        while (newsize > sz) {
            *vp++ = nil;
            sz++;
        }
    }
    else sz = newsize;
}

void ArrayOb::removeAll()
{
    register Object** vp = v;
    register unsigned i = sz;
    while (i--) *vp++ = nil;
}

unsigned ArrayOb::size() const  { return sz; }

void ArrayOb::allocSizeErr() const
{
    setError(NIHCL_ALLOCSIZE,DEFAULT,this,className());
}

void ArrayOb::indexRangeErr() const
{
    setError(NIHCL_INDEXRANGE,DEFAULT,this,className());
}

ArrayOb::ArrayOb(OIOin& strm)
    : BASE(strm)
{
    strm >> sz;
    v = new Object*[sz];
    for (register unsigned i=0; i<sz; i++)
        v[i] = Object::readFrom(strm);
}

void ArrayOb::storer(OIOout& strm) const
{
    BASE::storer(strm);
    strm << sz;
    for (register unsigned i=0; i<sz; i++)
        v[i]->storeOn(strm);
}

ArrayOb::ArrayOb(OIOifd& fd)
    : BASE(fd)
{
    fd >> sz;
    v = new Object*[sz];
    for (register unsigned i=0; i<sz; i++ )
        v[i] = Object::readFrom(fd);
}

void ArrayOb::storer(OIOofd& fd)  const
{
    Object::storer(fd);
    fd << sz;
    for (register unsigned i=0; i<sz; i++) 
        v[i]->storeOn(fd);
}

Object* ArrayOb::add(Object& ob)
{
    shouldNotImplement("add");
    return &ob;
}

unsigned ArrayOb::occurrencesOf(const Object&) const
{
    shouldNotImplement("occurrencesOf");
    return 0;
}

Object* ArrayOb::remove(const Object&)
{
    shouldNotImplement("remove");
    return 0;
}

// Not described in book:

void ArrayOb::sort()
{
    shouldNotImplement("sort");
}
