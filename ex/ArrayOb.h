#ifndef ARRAYOB_H
#define ARRAYOB_H

// ArrayOb.h -- Basic polymorphic array of objects

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ArrayOb.h,v 3.0 90/05/15 22:43:21 kgorlen Rel $

#include "Collection.h"

class Iterator;                                               // +

class ArrayOb: public Collection {
    DECLARE_MEMBERS(ArrayOb);
    Object** v;                                               // +
    unsigned sz;                                              // +
    void allocSizeErr() const;                                // +
    void indexRangeErr() const;                               // +
protected:              // storer() functions for object I/O
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
public:
    ArrayOb(unsigned size =DEFAULT_CAPACITY);                 // +
    ArrayOb(const ArrayOb&);                                  // +
    ~ArrayOb()  { delete v; }                                 // +
    void operator=(const ArrayOb&);                           // +
    bool operator==(const ArrayOb&) const;
    bool operator!=(const ArrayOb& a) const { return !(*this==a); }
    Object*& operator[](int i) {                              // +
        if ((unsigned)i >= sz) indexRangeErr();               // +
        return v[i];                                          // +
    }                                                         // +
    const Object *const& operator[](int i) const {            // +
        if ((unsigned)i >= sz) indexRangeErr();               // +
        return v[i];                                          // +
    }                                                         // +
    virtual Collection& addContentsTo(Collection&) const;     // +
    virtual Object*& at(int i);                               // +
    virtual const Object *const& at(int i) const;             // +
    virtual unsigned capacity() const;                        // +
    virtual int compare(const Object&) const;
    virtual void deepenShallowCopy();
    virtual Object* doNext(Iterator&) const;                  // +
    virtual unsigned hash() const;
    virtual bool isEqual(const Object&) const;
    virtual void reSize(unsigned);                            // +
    virtual void removeAll();                                 // +
    virtual unsigned size() const;                            // +
    virtual const Class* species() const;
private:                // shouldNotImplement();
    virtual Object* add(Object&);                             // +
    virtual unsigned occurrencesOf(const Object&) const;      // +
    virtual Object* remove(const Object&);                    // +
private:                // Not described in book              // +
    Object*& elem(int i)                    { return v[i]; }  // +
    const Object *const& elem(int i) const  { return v[i]; }  // +
    virtual void sort();                                      // +
};

#endif
