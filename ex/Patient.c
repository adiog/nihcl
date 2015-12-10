// Patient.c  -- Simple patient record class

#include "Patient.h"
#include "nihclIO.h"

#define THIS    Patient
#define BASE    Object
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES String::desc()
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(Patient,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Patient.c,v 3.0 90/05/15 22:43:56 kgorlen Rel $",NULL,NULL);

Patient::Patient(const String& nam, const String& num, int zip)
    : _name(nam), _ssn(num), _zip(zip)
{
}

bool Patient::operator==(const Patient& p) const
// Patient records will be considered equal when
// all members are equal
{
    return _name == p._name
        && _ssn == p._ssn
        && _zip == p._zip;
}

void Patient::operator=(const Patient& p)
{
    _name = p._name;
    _ssn = p._ssn;
    _zip = p._zip;
}

int Patient::compare(const Object& p) const
{
// verify that p has species Patient
    assertArgSpecies(p,classDesc,"compare");
// compare Patient names
    return _name.compare(((const Patient&)p)._name);   
}

void Patient::deepenShallowCopy()
{
    _name.deepenShallowCopy();
    _ssn.deepenShallowCopy();
}

unsigned Patient::hash() const
{
    return _name.hash() ^ _ssn.hash() ^ _zip;
}

bool Patient::isEqual(const Object& p) const
{
    return p.isSpecies(classDesc) && *this==(const Patient&)p;
}

void Patient::printOn(ostream& strm) const
{
    strm << _name << ' ' << _ssn << ' ' << _zip;
}

void Patient::dumpOn(ostream& strm) const
{
    strm << className() << '[' << endl;
    strm << "name:\t" << _name << endl;
    strm << "ssn:\t" << _ssn << endl;
    strm << "zip:\t" << _zip << endl;
    strm << ']' << endl;
}

Patient::Patient(OIOin& strm)
    : Object(strm), _name(strm), _ssn(strm)
{
    strm >> _zip;
}

void Patient::storer(OIOout& strm) const
{
    Object::storer(strm);
    _name.storeMemberOn(strm);
    _ssn.storeMemberOn(strm);
    strm << _zip;
}

Patient::Patient(OIOifd& fd)
    : Object(fd), _name(fd), _ssn(fd)
{
    fd >> _zip;
}

void Patient::storer(OIOofd& fd) const
{
    Object::storer(fd);
    _name.storeMemberOn(fd);
    _ssn.storeMemberOn(fd);
    fd << _zip;
}
