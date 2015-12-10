// ex14-2.c -- Counted pointers

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex14-2.c,v 3.0 90/05/15 22:44:57 kgorlen Rel $

#include "Patient.h"
#include "IdentDict.h"
#include "AssocInt.h"

class RefCountTable: public NIHCL {
    static IdentDict t;
public:
    static unsigned inc(const Object*);
    static unsigned dec(const Object*);
    static void printOn(ostream& strm =cout) {
        t.printOn(strm); strm << endl;
    }
};

unsigned RefCountTable::inc(const Object* p)
{
// Find ref count
    AssocInt* a =
        AssocInt::castdown((Object*)t.assocAt(*p));
    if (!a) {                               // no ref count for p
        t.add(*new AssocInt(*(Object*)p,1));    // create entry,
        return 1;                               // ref count=1
    }
    Integer& refct = *Integer::castdown(a->value());
    return refct.value(refct.value()+1);    // increment ref count
}

unsigned RefCountTable::dec(const Object* p)
{
    Integer& refct = *Integer::castdown(t.atKey(*p));
    unsigned n = refct.value(refct.value()-1);
    if (n == 0) delete t.removeKey(*p);
    return n;
}

IdentDict RefCountTable::t;

class Patient_CP: public NIHCL {
    Patient* p;
public:
    Patient_CP(Patient* pt)     { RefCountTable::inc(p = pt); }
    Patient_CP(const Patient_CP& cp)
        { RefCountTable::inc(p = cp.p); }
    ~Patient_CP()
        { if (RefCountTable::dec(p)==0) delete p; }
    Patient_CP& operator=(const Patient_CP&);
    Patient& operator*()        { return *p; }
    Patient& operator[](int i)  { return p[i]; }
    Patient* operator->()       { return p; }
};

Patient_CP& Patient_CP::operator=(const Patient_CP& cp)
{
    if (p != cp.p) {
        if (RefCountTable::dec(p) == 0) delete p;
        RefCountTable::inc(p = cp.p);
    }
    return *this;
}

main()
{
    Patient_CP cp1 =
        new Patient("Doe, John E","123-45-6789",20892);
    Patient_CP cp2 =
        new Patient("Doe, Jane F","987-65-4321",20892);
    Patient_CP* cpp = new Patient_CP(cp1);

    cout << "Initial RefCountTable:" << endl;
    RefCountTable::printOn(); cout << endl;

    cp1->printOn(); cout << endl;
    (*cp2).printOn(); cout << endl;
    (*cpp)->printOn(); cout << endl;

    cout << endl;
    cp2 = cp1;
    cp2->printOn(); cout << endl;
    cout << "\nRefCountTable after cp2 = cp1:" << endl;
    RefCountTable::printOn();

    delete cpp;
    cout << "\nRefCountTable after delete cpp:" << endl;
    RefCountTable::printOn();
}
