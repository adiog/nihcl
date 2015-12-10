// ex10-1.c -- Variations of isEqual()

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex10-1.c,v 3.0 90/05/15 22:44:15 kgorlen Rel $

// compile with -DSTRICT for strict equality
// compile with -DKINDOF to use isKindOf() instead of isSpecies()

#ifndef KINDOF
#define IS_SPECIES isSpecies
#else
#define IS_SPECIES isKindOf
#endif

#include "Object.h"

class Fruit: public Object {
    DECLARE_MEMBERS(Fruit);
    float weight;       // weight in grams
    float diameter;     // diameter in centimeters
protected:
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
public:
    Fruit(float w, float d) { weight = w; diameter = d; }
    float w() const         { return weight; }
    float d() const         { return diameter; }
    bool operator==(const Fruit&) const;
    virtual bool isEqual(const Object&) const;
    virtual const Class* species() const;
private:                // shouldNotImplement()
    virtual int compare(const Object&) const;
    virtual unsigned hash() const;
    virtual void printOn(ostream& strm =cout) const;
protected:              // shouldNotImplement()
    virtual void deepenShallowCopy();
};

#define THIS Fruit
#define BASE Object
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_ABSTRACT_CLASS(Fruit,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex10-1.c,v 3.0 90/05/15 22:44:15 kgorlen Rel $",NULL,NULL);

bool Fruit::operator==(const Fruit& f) const
{
    return weight==f.weight && diameter==f.diameter;
}

const Class* Fruit::species() const { return &classDesc; }

bool Fruit::isEqual(const Object& f) const
{
    return f.IS_SPECIES(classDesc) && *this==(const Fruit&)f;
}

#undef THIS
#undef BASE
#undef BASE_CLASSES
#undef MEMBER_CLASSES
#undef VIRTUAL_BASE_CLASSES

class Apple: public Fruit {
    DECLARE_MEMBERS(Apple);
public:
    enum appleVariety
        { MCINTOSH, JONATHAN, REDDELICIOUS, STAYMAN };
private:
    appleVariety variety;
protected:
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
public:
    Apple(appleVariety v, float w, float d) : Fruit(w,d) {
        variety = v;
    }
    bool operator==(const Apple&) const;
#ifdef STRICT
    virtual const Class* species() const;
    virtual bool isEqual(const Object&) const;
#endif
};

#define THIS Apple
#define BASE Fruit
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(Apple,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex10-1.c,v 3.0 90/05/15 22:44:15 kgorlen Rel $",NULL,NULL);

bool Apple::operator==(const Apple& a) const
{
    return variety==a.variety && Fruit::operator==(a);
}

#ifdef STRICT
const Class* Apple::species() const { return &classDesc; }

bool Apple::isEqual(const Object& a) const
{
    return a.IS_SPECIES(classDesc) && *this==(const Apple&)a;
}
#endif

#undef THIS
#undef BASE
#undef BASE_CLASSES
#undef MEMBER_CLASSES
#undef VIRTUAL_BASE_CLASSES

class Orange: public Fruit {
    DECLARE_MEMBERS(Orange);
public:
    enum orangeVariety { NAVAL, FLORIDA, CALIFORNIA };
private:
    orangeVariety variety;
protected:
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
public:
    Orange(orangeVariety v, float w, float d) : Fruit(w,d) {
        variety = v;
    }
    bool operator==(const Orange&) const;
#ifdef STRICT
    virtual const Class* species() const;
    virtual bool isEqual(const Object&) const;
#endif
};

#define THIS Orange
#define BASE Fruit
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(Orange,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex10-1.c,v 3.0 90/05/15 22:44:15 kgorlen Rel $",NULL,NULL);

bool Orange::operator==(const Orange& o) const
{
    return variety==o.variety && Fruit::operator==(o);
}

#ifdef STRICT
const Class* Orange::species() const { return &classDesc; }

bool Orange::isEqual(const Object& a) const
{
    return a.IS_SPECIES(classDesc) && *this==(const Orange&)a;
}
#endif

#undef THIS
#undef BASE
#undef BASE_CLASSES
#undef MEMBER_CLASSES
#undef VIRTUAL_BASE_CLASSES

main()
{
    Fruit f(100.0, 8.5);
    Apple a(Apple::MCINTOSH, 100.0, 8.5);
    Orange o(Orange::NAVAL, 100.0, 8.5);
#ifdef STRICT
    cout << "Strict equality, ";
#else
    cout << "Loose equality, ";
#endif
#ifndef KINDOF
    cout << "isSpecies() comparability\n";
#else
    cout << "isKindOf() comparability\n";
#endif
    cout << "f.isEqual(a): " << (f.isEqual(a) ? "YES" : "NO")
        << endl;
    cout << "a.isEqual(f): " << (a.isEqual(f) ? "YES" : "NO")
        << endl;
    cout << "a.isEqual(o): " << (a.isEqual(o) ? "YES" : "NO")
        << endl;
}

#include "nihclIO.h"

#define BASE Object

int Fruit::compare(const Object&) const
{
    shouldNotImplement("compare");
    return 0;
}

void Fruit::deepenShallowCopy()
{
    shouldNotImplement("deepenShallowCopy");
    return;
}

unsigned Fruit::hash() const
{
    shouldNotImplement("hash");
    return 0;
}

void Fruit::printOn(ostream&) const
{
    shouldNotImplement("printOn");
    return;
}


Fruit::Fruit(OIOin& strm)
    : BASE(strm)
{
    strm >> weight >> diameter;
}

void Fruit::storer(OIOout& strm) const
{
    BASE::storer(strm);
    strm << weight << diameter;
}

Fruit::Fruit(OIOifd& fd)
    : BASE(fd)
{
    fd >> weight >> diameter;
}

void Fruit::storer(OIOofd& fd) const
{
    BASE::storer(fd);
    fd << weight << diameter;
}

#undef BASE
#define BASE Fruit

Apple::Apple(OIOin& strm)
    : BASE(strm)
{
    strm >> (int)variety;
}

void Apple::storer(OIOout& strm) const
{
    BASE::storer(strm);
    strm << variety;
}

Apple::Apple(OIOifd& fd)
    : BASE(fd)
{
    fd >> (int)variety;
}

void Apple::storer(OIOofd& fd) const
{
    BASE::storer(fd);
    fd << variety;
}

#undef BASE
#define BASE Fruit

Orange::Orange(OIOin& strm)
    : BASE(strm)
{
    strm >> (int)variety;
}

void Orange::storer(OIOout& strm) const
{
    BASE::storer(strm);
    strm << variety;
}

Orange::Orange(OIOifd& fd)
    : BASE(fd)
{
    fd >> (int)variety;
}

void Orange::storer(OIOofd& fd) const
{
    BASE::storer(fd);
    fd << variety;
}

#undef BASE
