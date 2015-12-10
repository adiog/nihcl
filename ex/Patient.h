#ifndef PATIENT_H
#define PATIENT_H

// Patient.h -- Simple patient record class

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Patient.h,v 3.0 90/05/15 22:43:57 kgorlen Rel $

#include "Object.h"
#include "String.h"

class Patient: public Object {
    DECLARE_MEMBERS(Patient);
    String _name;       // last name, first name, middle initial
    String _ssn;        // social security number: ddd-dd-dddd
    int _zip;           // ZIP code : ddddd
protected:          // storer() functions for object I/O
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
public:
    Patient(const String& nam, const String& num, int zip);

    String name() const         { return _name; }
    String ssn() const          { return _ssn; }
    int zip() const             { return _zip; }

    bool operator==(const Patient&) const;
    bool operator!=(const Patient& a) const { return !(*this==a); }
    void operator=(const Patient&);

    virtual int compare(const Object&) const;
    virtual void deepenShallowCopy();
    virtual void dumpOn(ostream& strm =cerr) const;
    virtual unsigned hash() const;
    virtual bool isEqual(const Object&) const;
    virtual void printOn(ostream& strm =cout) const;
};

#endif
